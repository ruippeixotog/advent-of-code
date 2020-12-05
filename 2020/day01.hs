import Control.Arrow

solve1 :: [Int] -> Int
solve1 xs = head [a * b | a <- xs, b <- xs, a + b == 2020]

solve2 :: [Int] -> Int
solve2 xs = head [a * b * c | a <- xs, b <- xs, c <- xs, a + b + c == 2020]

parseInput :: String -> [Int]
parseInput = map read . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
