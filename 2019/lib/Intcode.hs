{-# LANGUAGE FlexibleInstances #-}
  
module Lib.Intcode
  ( Prog,
    ProgMonad,
    parseProg,
    runProgMonad,
    runProg,
    readData,
    writeData,
    pushInput,
    allOutputs,
    popOutput,
  )
where

import Control.Monad
import Control.Monad.State.Lazy (State, gets, modify, runState)
import Data.Bool
import qualified Data.IntMap as IM
import Data.Sequence (Seq (..))
import qualified Data.Sequence as Seq

type Prog = IM.IntMap Int

data ProgState = ProgState
  { sProg :: Prog,
    sPc :: Int,
    sIns :: Seq Int,
    sOuts :: Seq Int
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
  let st = ProgState {sProg = prog, sPc = 0, sIns = Seq.empty, sOuts = Seq.empty}
   in fst $ runState op st

runProg :: ProgMonad ()
runProg = do
  stmt <- nextStmt
  -- trace (show stmt) $
  case stmt of
    Add a b c -> do
      writeData c (a + b)
      runProg
    Mul a b c -> do
      writeData c (a * b)
      runProg
    Read a -> do
      inVal <- popInput
      writeData a inVal
      runProg
    Write a -> do
      pushOutput a
      runProg
    Jnz a b -> do
      when (a /= 0) $ writePc b
      runProg
    Jz a b -> do
      when (a == 0) $ writePc b
      runProg
    Lt a b c -> do
      writeData c (bool 0 1 $ a < b)
      runProg
    Eq a b c -> do
      writeData c (bool 0 1 $ a == b)
      runProg
    Halt ->
      return ()

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
popInput = do
  ins <- gets sIns
  case ins of
    next :<| rest -> do
      modify (\s -> s {sIns = rest})
      return next
    _ ->
      error "No inputs left"

allOutputs :: ProgMonad (Seq Int)
allOutputs = gets sOuts

pushOutput :: Int -> ProgMonad ()
pushOutput val = modify (\s -> s {sOuts = sOuts s :|> val})

popOutput :: ProgMonad Int
popOutput = do
  outs <- gets sOuts
  case outs of
    next :<| rest -> do
      modify (\s -> s {sOuts = rest})
      return next
    _ ->
      error "No outputs left"
