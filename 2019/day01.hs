solve1 :: [Int] -> Int
solve1 = sum . map fuel
  where
    fuel n = n `div` 3 - 2

solve2 :: [Int] -> Int
solve2 = sum . map fuel
  where
    fuel 0 = 0
    fuel n =
      let f0 = max 0 $ n `div` 3 - 2
       in f0 + fuel f0

parseInput :: String -> [Int]
parseInput = map read . lines

main :: IO ()
main = interact $ show . tee solve1 solve2 . parseInput
  where
    tee f1 f2 arg = (f1 arg, f2 arg)
