module Lib.Intcode where

import Control.Applicative (liftA3)
import Control.Monad.State.Lazy (State, gets, modify, runState)
import qualified Data.IntMap as IM

type Prog = IM.IntMap Int

data ProgState = ProgState
  { sProg :: Prog,
    sPc :: Int
  }

data Stmt
  = Add Int Int Int
  | Mul Int Int Int
  | Halt
  deriving (Show)

type ProgMonad a = State ProgState a

parseProg :: String -> Prog
parseProg = IM.fromList . zip [0 ..] . map read . codes
  where
    codes str = words [if c == ',' then ' ' else c | c <- str]

runProgMonad :: ProgMonad a -> Prog -> a
runProgMonad op prog = fst $ runState op $ ProgState {sProg = prog, sPc = 0}

runProg :: ProgMonad ()
runProg = do
  stmt <- nextStmt
  -- trace (show stmt) $
  case stmt of
    Add a b c -> do
      aVal <- readData a
      bVal <- readData b
      writeData c (aVal + bVal)
      runProg
    Mul a b c -> do
      aVal <- readData a
      bVal <- readData b
      writeData c (aVal * bVal)
      runProg
    Halt ->
      return ()

nextStmt :: ProgMonad Stmt
nextStmt = do
  opcode <- nextOpcode
  case opcode of
    1 -> (liftA3 Add) nextOpcode nextOpcode nextOpcode
    2 -> (liftA3 Mul) nextOpcode nextOpcode nextOpcode
    99 -> return Halt
    op -> error $ "Invalid opcode: " <> show op

nextOpcode :: ProgMonad Int
nextOpcode = do
  pc <- gets sPc
  opcode <- readData pc
  writePc $ pc + 1
  return opcode

readData :: Int -> ProgMonad Int
readData pos = gets $ (IM.! pos) . sProg

writeData :: Int -> Int -> ProgMonad ()
writeData pos val = modify (\s -> s {sProg = IM.insert pos val (sProg s)})

writePc :: Int -> ProgMonad ()
writePc val = modify (\s -> s {sPc = val})
