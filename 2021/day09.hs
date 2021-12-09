import Control.Arrow
import Data.HashMap.Strict (HashMap)
import qualified Data.HashMap.Strict as Map
import Data.List
import Data.Maybe
import Data.Ord

type Coord = (Int, Int)

toMap :: [[Int]] -> HashMap Coord Int
toMap =
  Map.filter (/= 9) . Map.fromList . concat
    . zipWith (\i -> zipWith (\j c -> ((i, j), c)) [0 ..]) [0 ..]

sink :: HashMap Coord Int -> Coord -> Coord
sink grid loc@(i, j) =
  if grid Map.! minAdj < grid Map.! loc then sink grid minAdj else loc
  where
    adjs = filter (`Map.member` grid) [(i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)]
    minAdj = minimumBy (comparing (grid Map.!)) adjs

--------

solve1 :: [[Int]] -> Int
solve1 xs = sum $ map risk $ nub $ sink grid <$> Map.keys grid
  where
    grid = toMap xs
    risk loc = 1 + grid Map.! loc

solve2 :: [[Int]] -> Int
solve2 xs = product $ take 3 $ sortOn Down $ Map.elems $ hist $ sink grid <$> Map.keys grid
  where
    grid = toMap xs
    hist = foldr (Map.alter $ Just . (+ 1) . fromMaybe 0) Map.empty

parseInput :: String -> [[Int]]
parseInput = map (map (read . (: []))) . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
