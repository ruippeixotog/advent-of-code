import Control.Arrow
import Data.Bool
import Data.List
import Data.Maybe

solve1 :: [Int] -> Int
solve1 = head . mapMaybe match . tails
  where
    match xs = case splitAt 25 xs of
      (xs, k : _) -> bool Nothing (Just k) $ and [x1 + x2 /= k | x1 <- xs, x2 <- xs]
      _ -> Nothing

solve2 :: [Int] -> Int
solve2 inp = uncurry (+) $ (minimum &&& maximum) $ head $ filter isValid $ sublists inp
  where
    res1 = solve1 inp
    sublists = concatMap inits . tails
    isValid xs@(_ : _ : _) = sum xs == res1
    isValid _ = False

parseInput :: String -> [Int]
parseInput = map read . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
