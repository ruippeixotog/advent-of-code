import Control.Arrow
import qualified Data.HashMap.Strict as Map
import Data.List

run :: [Int] -> [Int]
run initials = unfoldr (Just . step) (1, (-1, Map.empty), initials)
  where
    step (it, (_, hist), x : xs) = (x, (it + 1, Map.alterF (alterFun it) x hist, xs))
    step (it, (next, hist), []) = (next, (it + 1, Map.alterF (alterFun it) next hist, []))
    alterFun it Nothing = (0, Just it)
    alterFun it (Just prev) = (it - prev, Just it)

solve1 :: [Int] -> Int
solve1 = last . take 2020 . run

solve2 :: [Int] -> Int
solve2 = last . take 30000000 . run

input :: [Int]
input = [9, 3, 1, 0, 8, 4]

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . const input
