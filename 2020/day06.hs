{-# LANGUAGE OverloadedStrings #-}

import Control.Arrow
import Data.Foldable
import Data.Set (Set)
import qualified Data.Set as Set
import qualified Data.Text as T

solve1 :: [[Set Char]] -> Int
solve1 = sum . map (length . fold)

solve2 :: [[Set Char]] -> Int
solve2 = sum . map (length . foldr1 Set.intersection)

parseInput :: String -> [[Set Char]]
parseInput = map (map Set.fromList . words . T.unpack) . T.splitOn "\n\n" . T.pack

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
