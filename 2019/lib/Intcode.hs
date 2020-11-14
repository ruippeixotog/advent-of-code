module Lib.Intcode
  ( Prog,
    ProgMonad,
    parseProg,
    runProgMonad,
    runProg,
    readData,
    writeData,
    pushInput,
    popOutput,
    lastOutput,
  )
where

import Control.Monad
import Control.Monad.State.Strict
import Data.Bool
import Data.Foldable
import qualified Data.IntMap as IM
import Data.Sequence (Seq (..))
import qualified Data.Sequence as Seq

type Prog = IM.IntMap Int

data ProgState = ProgState
  { sProg :: Prog,
    sPc :: Int,
    sIns :: Seq Int,
    sOuts :: Seq Int,
    sHalted :: Bool
  }

data Stmt
  = Add Int Int Int
  | Mul Int Int Int
  | Read Int
  | Write Int
  | Jnz Int Int
  | Jz Int Int
  | Lt Int Int Int
  | Eq Int Int Int
  | Halt
  deriving (Show)

type ProgMonad a = State ProgState a

-----------------------------

parseProg :: String -> Prog
parseProg = IM.fromList . zip [0 ..] . map read . codes
  where
    codes str = words [if c == ',' then ' ' else c | c <- str]

runProgMonad :: ProgMonad a -> Prog -> a
runProgMonad op prog =
  let st = ProgState prog 0 Seq.empty Seq.empty False
   in fst $ runState op st

runProg :: ProgMonad ()
runProg = do
  halted <- gets sHalted
  unless halted $ do
    stmt <- nextStmt
    -- trace (show stmt) $
    case stmt of
      Add a b c -> writeData c $ a + b
      Mul a b c -> writeData c $ a * b
      Read a -> writeData a =<< popInput
      Write a -> pushOutput a
      Jnz a b -> when (a /= 0) $ writePc b
      Jz a b -> when (a == 0) $ writePc b
      Lt a b c -> writeData c $ bool 0 1 $ a < b
      Eq a b c -> writeData c $ bool 0 1 $ a == b
      Halt -> modify (\s -> s {sHalted = True})
    runProg

nextStmt :: ProgMonad Stmt
nextStmt = do
  opcode <- nextOpcode
  let mode idx = opcode `div` 10 ^ (1 + idx :: Int) `rem` 10
      nextArg idx = derefArg (mode idx) =<< nextOpcode
      derefArg 0 pos = readData pos
      derefArg 1 val = return val
      derefArg m _ = error $ "Invalid mode: " <> show m
   in case opcode `rem` 100 of
        1 -> (liftM3 Add) (nextArg 1) (nextArg 2) nextOpcode
        2 -> (liftM3 Mul) (nextArg 1) (nextArg 2) nextOpcode
        3 -> (liftM Read) nextOpcode
        4 -> (liftM Write) (nextArg 1)
        5 -> (liftM2 Jnz) (nextArg 1) (nextArg 2)
        6 -> (liftM2 Jz) (nextArg 1) (nextArg 2)
        7 -> (liftM3 Lt) (nextArg 1) (nextArg 2) nextOpcode
        8 -> (liftM3 Eq) (nextArg 1) (nextArg 2) nextOpcode
        99 -> return Halt
        op -> error $ "Invalid opcode: " <> show op

nextOpcode :: ProgMonad Int
nextOpcode = do
  pc <- gets sPc
  opcode <- readData pc
  writePc $ pc + 1
  return opcode

-----------------------------

readData :: Int -> ProgMonad Int
readData pos = gets $ (IM.! pos) . sProg

writeData :: Int -> Int -> ProgMonad ()
writeData pos val = modify (\s -> s {sProg = IM.insert pos val (sProg s)})

writePc :: Int -> ProgMonad ()
writePc val = modify (\s -> s {sPc = val})

pushInput :: Int -> ProgMonad ()
pushInput val = modify (\s -> s {sIns = sIns s :|> val})

popInput :: ProgMonad Int
popInput = popSeq sIns $ \val s -> s {sIns = val}

pushOutput :: Int -> ProgMonad ()
pushOutput val = modify (\s -> s {sOuts = sOuts s :|> val})

popOutput :: ProgMonad Int
popOutput = popSeq sOuts $ \val s -> s {sOuts = val}

lastOutput :: ProgMonad Int
lastOutput = last . toList <$> gets sOuts

popSeq :: (ProgState -> Seq a) -> (Seq a -> ProgState -> ProgState) -> ProgMonad a
popSeq getter setter = do
  elems <- gets getter
  case elems of
    next :<| rest -> do
      modify $ setter rest
      return next
    _ ->
      error "Queue is empty"
