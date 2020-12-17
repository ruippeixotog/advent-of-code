{-# LANGUAGE TupleSections #-}

import Control.Arrow
import Data.Foldable
import Data.List
import Data.Set (Set)
import qualified Data.Set as Set

adjCube :: [Int] -> [[Int]]
adjCube [] = [[]]
adjCube (x : xs) = [x + d : adjs | d <- [-1, 0, 1], adjs <- adjCube xs]

simulate :: Int -> Set [Int] -> Set [Int]
simulate 0 grid = grid
simulate n grid = simulate (n - 1) $ step grid
  where
    step = Set.filter isActive . fold . Set.map (Set.fromList . adjCube)
    activeAdjs pos = length $ filter (/= pos) $ filter (`Set.member` grid) $ adjCube pos
    isActive pos = activeAdjs pos == 3 || pos `Set.member` grid && activeAdjs pos == 2

solve1 :: [(Int, Int)] -> Int
solve1 = length . simulate 6 . Set.fromList . map (\(i, j) -> [i, j, 0])

solve2 :: [(Int, Int)] -> Int
solve2 = length . simulate 6 . Set.fromList . map (\(i, j) -> [i, j, 0, 0])

parseInput :: String -> [(Int, Int)]
parseInput = concat . zipWith (\i js -> (i,) <$> js) [0 ..] . map (elemIndices '#') . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
