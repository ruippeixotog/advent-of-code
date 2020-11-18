import Control.Arrow
import Data.Bifunctor (bimap)
import Data.List (unfoldr)

digits :: Int -> [Int]
digits = reverse . unfoldr (\x -> if x == 0 then Nothing else Just (mod x 10, div x 10))

hasTwoAdj :: [Int] -> Bool
hasTwoAdj (a : b : rest) = a == b || hasTwoAdj (b : rest)
hasTwoAdj _ = False

hasExactlyTwoAdj :: [Int] -> Bool
hasExactlyTwoAdj [] = False
hasExactlyTwoAdj (a : rest) =
  let (prefix, rest') = span (== a) rest
   in length prefix == 1 || hasExactlyTwoAdj rest'

nonDecreasing :: [Int] -> Bool
nonDecreasing (a : b : rest) = a <= b && nonDecreasing (b : rest)
nonDecreasing _ = True

solve1 :: (Int, Int) -> Int
solve1 (st, end) =
  length $ filter hasTwoAdj $ filter nonDecreasing $ map digits [st .. end]

solve2 :: (Int, Int) -> Int
solve2 (st, end) =
  length $ filter hasExactlyTwoAdj $ filter nonDecreasing $ map digits [st .. end]

parseInput :: String -> (Int, Int)
parseInput str = bimap read (read . tail) $ break (== '-') str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
