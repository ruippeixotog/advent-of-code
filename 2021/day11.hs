import Control.Arrow
import Data.List
import Data.Map.Strict (Map)
import qualified Data.Map.Strict as Map
import Data.Maybe

type Coord = (Int, Int)

toMap :: [[Int]] -> Map Coord Int
toMap = Map.fromList . concat . zipWith (\i -> zipWith (\j c -> ((i, j), c)) [0 ..]) [0 ..]

simulate :: Map Coord Int -> [Int]
simulate initial = map fst $ iterate (step . snd) (0, initial)
  where
    step = flash [] . Map.map (+ 1)

    flash visited grid =
      case first Map.keys $ Map.partition (>= 10) grid of
        ([], rest) -> (length visited, foldr (`Map.insert` 0) rest visited)
        (bright, rest) ->
          flash (bright <> visited) $ foldr (Map.adjust (+ 1)) rest $ concatMap adjs bright

    adjs (i, j) =
      filter (`Map.member` initial) $
        [(i + di, j + dj) | di <- [-1 .. 1], dj <- [-1 .. 1], di /= 0 || dj /= 0]

solve1 :: [[Int]] -> Int
solve1 = sum . take 101 . simulate . toMap

solve2 :: [[Int]] -> Int
solve2 = fromJust . elemIndex 100 . simulate . toMap

parseInput :: String -> [[Int]]
parseInput = map (map (read . (: []))) . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
