import Control.Arrow
import Data.Char
import Data.Map (Map)
import qualified Data.Map as Map
import Data.Set (Set)
import qualified Data.Set as Set
import Data.Tuple

toGraph :: [(String, String)] -> Map String [String]
toGraph xs = Map.fromListWith (++) $ second (: []) <$> xs ++ map swap xs

dfs :: Bool -> Set String -> Map String [String] -> String -> Int
dfs _ _ _ "end" = 1
dfs didTwice visited g curr
  | limited && not canDoTwice = 0
  | limited = dfs True (Set.delete curr visited) g curr
  | otherwise = sum $ dfs didTwice (Set.insert curr visited) g <$> g Map.! curr
  where
    limited = isLower (head curr) && Set.member curr visited
    canDoTwice = curr /= "start" && not didTwice

solve1 :: [(String, String)] -> Int
solve1 = flip (dfs True Set.empty) "start" . toGraph

solve2 :: [(String, String)] -> Int
solve2 = flip (dfs False Set.empty) "start" . toGraph

parseInput :: String -> [(String, String)]
parseInput = map (second tail . break (== '-')) . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
