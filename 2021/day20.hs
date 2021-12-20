import Control.Arrow
import Data.Bits
import Data.List
import Data.Map.Strict (Map)
import qualified Data.Map.Strict as Map
import Data.Maybe

binToInt :: [Bool] -> Int
binToInt bools = foldl setBit 0 $ findIndices id $ reverse bools

toMap :: [[a]] -> Map (Int, Int) a
toMap = Map.fromList . concat . zipWith (\i -> zipWith (\j c -> ((i, j), c)) [0 ..]) [0 ..]

step :: [Bool] -> (Bool, Map (Int, Int) Bool) -> (Bool, Map (Int, Int) Bool)
step algo (def, grid) = (newDef, update $ expand grid)
  where
    expand m = foldr (Map.alter (Just . fromMaybe def)) m $ concatMap adjs $ Map.keys m
    update = Map.mapWithKey (\k _ -> algo !! algoIndex k)

    adjs (i, j) = [(i + di, j + dj) | di <- [-1 .. 1], dj <- [-1 .. 1]]
    algoIndex = binToInt . map (fromMaybe def . (grid Map.!?)) . adjs
    newDef = if def then last algo else head algo

simulate :: [Bool] -> Int -> Map (Int, Int) Bool -> Int
simulate algo n grid = Map.size $ Map.filter id $ snd $ (!! n) $ iterate (step algo) (False, grid)

solve1 :: ([Bool], [[Bool]]) -> Int
solve1 (algo, grid) = simulate algo 2 $ toMap grid

solve2 :: ([Bool], [[Bool]]) -> Int
solve2 (algo, grid) = simulate algo 50 $ toMap grid

parseInput :: String -> ([Bool], [[Bool]])
parseInput = (head &&& tail) . map (map (== '#')) . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
