{-# LANGUAGE TupleSections #-}

import Control.Arrow
import Data.List
import Data.Maybe

solve1 :: [Int] -> Int
solve1 = uncurry (*) . (count 1 &&& (+ 1) . count 3) . mapMaybe diff2 . tails . (0 :) . sort
  where
    count x = length . filter (== x)
    diff2 (x0 : x1 : _) = Just $ x1 - x0
    diff2 _ = Nothing

solve2 :: [Int] -> Int
solve2 = snd . last . foldl combine [(0, 1)] . map (,0) . sort
  where
    combine [] (k1, cnt1) = [(k1, cnt1)]
    combine ((k0, cnt0) : rest) (k1, cnt1)
      | k1 - k0 > 3 = combine rest (k1, cnt1)
      | otherwise = (k0, cnt0) : combine rest (k1, cnt1 + cnt0)

parseInput :: String -> [Int]
parseInput = map read . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
