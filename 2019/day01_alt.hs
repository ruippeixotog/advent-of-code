calcFuel1 :: Int -> Int
calcFuel1 m = m `div` 3 - 2

calcFuel2 :: Int -> Int
calcFuel2 0 = 0
calcFuel2 m = fuel + calcFuel2 fuel
  where fuel = max 0 (calcFuel1 m)

solve :: (Int -> Int) -> [Int] -> Int
solve calcFuel = sum . map calcFuel

input :: IO [Int]
input = map read . lines <$> getContents

main :: IO ()
main = do
  inp <- input
  print $ solve calcFuel1 inp
  print $ solve calcFuel2 inp
