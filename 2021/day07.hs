import Control.Arrow
import Data.List.Split

findCost :: (Int -> Int) -> [Int] -> Int
findCost cost xs = minimum [totalCost tgt xs | tgt <- [minimum xs..maximum xs]]
  where
    totalCost tgt = sum . map (cost . abs . (`subtract` tgt))

solve1 :: [Int] -> Int
solve1 = findCost id

solve2 :: [Int] -> Int
solve2 = findCost (\x -> x * (x + 1) `div` 2)

parseInput :: String -> [Int]
parseInput = map read . splitOn ","

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
