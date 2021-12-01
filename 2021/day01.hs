import Control.Arrow

solve1 :: [Int] -> Int
solve1 (x1 : x2 : xs) = fromEnum (x2 > x1) + solve1 (x2 : xs)
solve1 _ = 0

solve2 :: [Int] -> Int
solve2 = solve1 . sums
  where
    sums (x1 : x2 : x3 : xs) = (x1 + x2 + x3) : sums (x2 : x3 : xs)
    sums _ = []

parseInput :: String -> [Int]
parseInput = map read . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
