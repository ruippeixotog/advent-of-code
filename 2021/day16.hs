{-# LANGUAGE LambdaCase #-}

import Control.Arrow
import Control.Monad.State
import Data.Bits
import Data.List
import Numeric

data Packet = Packet Int Payload

data Payload = Lit Int | Op OpType [Packet]

data OpType = Sum | Product | Min | Max | Gt | Lt | Eq

type BitState = State [Bool]

readN :: Int -> BitState [Bool]
readN = state . splitAt

hexToBin :: Char -> [Bool]
hexToBin ch = testBit (fst $ head $ readHex [ch] :: Int) <$> [3, 2 .. 0]

binToInt :: [Bool] -> Int
binToInt = foldl setBit 0 . findIndices id . reverse

readPacket :: BitState Packet
readPacket = readN 3 >>= \ver -> Packet (binToInt ver) <$> readPayload

readPayload :: BitState Payload
readPayload =
  readN 3 >>= \case
    [False, False, False] -> Op Sum <$> readArgs
    [False, False, True] -> Op Product <$> readArgs
    [False, True, False] -> Op Min <$> readArgs
    [False, True, True] -> Op Max <$> readArgs
    [True, False, False] -> Lit . binToInt <$> readLit
    [True, False, True] -> Op Gt <$> readArgs
    [True, True, False] -> Op Lt <$> readArgs
    [True, True, True] -> Op Eq <$> readArgs
    _ -> error "Illegal payload type"

readLit :: BitState [Bool]
readLit =
  readN 5 >>= \case
    (True : lit) -> (lit ++) <$> readLit
    (False : lit) -> return lit
    _ -> error "Illegal literal"

readArgs :: BitState [Packet]
readArgs =
  readN 1 >>= \case
    [False] -> do
      len <- readN 15
      unfoldr consume <$> readN (binToInt len)
      where
        consume [] = Nothing
        consume bits = Just $ runState readPacket bits
    [True] -> do
      n <- readN 11
      replicateM (binToInt n) readPacket
    _ -> error "Illegal arguments"

solve1 :: String -> Int
solve1 = sumVersions . evalState readPacket . concatMap hexToBin
  where
    sumVersions (Packet v (Op _ args)) = v + sum (sumVersions <$> args)
    sumVersions (Packet v _) = v

solve2 :: String -> Int
solve2 = calc . evalState readPacket . concatMap hexToBin
  where
    calc (Packet _ (Op Sum args)) = sum $ calc <$> args
    calc (Packet _ (Op Product args)) = product $ calc <$> args
    calc (Packet _ (Op Min args)) = minimum $ calc <$> args
    calc (Packet _ (Op Max args)) = maximum $ calc <$> args
    calc (Packet _ (Lit val)) = val
    calc (Packet _ (Op Gt [lhs, rhs])) = fromEnum $ calc lhs > calc rhs
    calc (Packet _ (Op Lt [lhs, rhs])) = fromEnum $ calc lhs < calc rhs
    calc (Packet _ (Op Eq [lhs, rhs])) = fromEnum $ calc lhs == calc rhs
    calc _ = error "Illegal packet"

parseInput :: String -> String
parseInput = head . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
