import Control.Arrow
import Data.Char
import Data.Foldable
import Data.Set (Set)
import qualified Data.Set as Set

data Dir = E | SE | SW | W | NW | NE deriving (Bounded, Enum, Read)

move :: (Int, Int) -> Dir -> (Int, Int)
move (x, y) E = (x + 2, y)
move (x, y) SE = (x + 1, y - 1)
move (x, y) SW = (x - 1, y - 1)
move (x, y) W = (x - 2, y)
move (x, y) NW = (x - 1, y + 1)
move (x, y) NE = (x + 1, y + 1)

initialize :: [[Dir]] -> Set (Int, Int)
initialize = foldl compute Set.empty . map (foldl move (0, 0))
  where
    compute set target
      | target `Set.member` set = Set.delete target set
      | otherwise = Set.insert target set

adjs :: (Int, Int) -> [(Int, Int)]
adjs pos = move pos <$> [minBound .. maxBound]

simulate :: Int -> Set (Int, Int) -> Set (Int, Int)
simulate 0 grid = grid
simulate n grid = simulate (n - 1) $ step grid
  where
    step = Set.filter isBlack . fold . Set.map (Set.fromList . adjs)
    isBlack pos = blackAdjs pos == 2 || pos `Set.member` grid && blackAdjs pos == 1
    blackAdjs = length . filter (`Set.member` grid) . adjs

solve1 :: [[Dir]] -> Int
solve1 = length . initialize

solve2 :: [[Dir]] -> Int
solve2 = length . simulate 100 . initialize

parseInput :: String -> [[Dir]]
parseInput = map parseTile . lines . map toUpper
  where
    parseTile [] = []
    parseTile ('S' : b : rest) = read ['S', b] : parseTile rest
    parseTile ('N' : b : rest) = read ['N', b] : parseTile rest
    parseTile (a : rest) = read [a] : parseTile rest

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
