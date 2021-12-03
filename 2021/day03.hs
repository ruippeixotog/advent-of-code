import Control.Arrow
import Data.Bits
import Data.Char (digitToInt)
import Data.List
import Data.Ord (comparing)

binToInt :: [Bool] -> Int
binToInt = foldl (\i b -> fromEnum b .|. i `shiftL` 1) 0

mostFrequent :: Ord a => [a] -> a
mostFrequent = head . maximumBy (comparing length) . group . sort

solve1 :: [[Bool]] -> Int
solve1 xs = binToInt gamma * binToInt epsilon
  where
    gamma = map mostFrequent $ transpose xs
    epsilon = map not gamma

solve2 :: [[Bool]] -> Int
solve2 xs = binToInt oxygen * binToInt co2
  where
    oxygen = process (>=) 0 xs
    co2 = process (<) 0 xs

    process _ _ [x] = x
    process cmp pos xs' =
      process cmp (pos + 1) (if length xs1 `cmp` length xs0 then xs1 else xs0)
      where
        (xs1, xs0) = partition (!! pos) xs'

parseInput :: String -> [[Bool]]
parseInput = map (map $ toEnum . digitToInt) . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
