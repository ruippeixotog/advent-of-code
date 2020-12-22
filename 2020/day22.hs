import Control.Arrow
import Data.Bool
import Data.List.Split
import qualified Data.Set as Set

score :: [Int] -> Int
score = sum . zipWith (*) [1 ..] . reverse

solve1 :: ([Int], [Int]) -> Int
solve1 (xs, []) = score xs
solve1 ([], ys) = score ys
solve1 (x : xs, y : ys)
  | x > y = solve1 (xs ++ [x, y], ys)
  | otherwise = solve1 (xs, ys ++ [y, x])

solve2 :: ([Int], [Int]) -> Int
solve2 = score . snd . playMem Set.empty
  where
    playMem mem st
      | Set.member st mem = (False, fst st)
      | otherwise = play (Set.insert st mem) st
    play _ (xs, []) = (False, xs)
    play _ ([], ys) = (True, ys)
    play mem (x : xs, y : ys) =
      let winner = if x <= length xs && y <= length ys
                   then fst $ playMem Set.empty (take x xs, take y ys)
                   else x < y
       in playMem mem $ bool (xs ++ [x, y], ys) (xs, ys ++ [y, x]) winner

parseInput :: String -> ([Int], [Int])
parseInput = ((!! 0) &&& (!! 1)) . map (map read . tail . lines) . splitOn "\n\n"

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
