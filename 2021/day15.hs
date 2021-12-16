import Control.Arrow
import Data.HashMap.Strict (HashMap)
import qualified Data.HashMap.Strict as Map
import qualified Data.Set as Set

type Coord = (Int, Int)

toMap :: [[Int]] -> HashMap Coord Int
toMap = Map.fromList . concat . zipWith (\i -> zipWith (\j c -> ((i, j), c)) [0 ..]) [0 ..]

dikjstra :: HashMap Coord Int -> Coord -> Coord -> Int
dikjstra grid src tgt = next Set.empty $ Set.singleton (0, src)
  where
    next visited q =
      let ((dist, curr), q') = first (head . Set.toList) $ Set.splitAt 1 q
       in process visited dist curr q'

    process visited dist curr q
      | curr == tgt = dist
      | curr `Set.member` visited = next visited q
      | otherwise = next (Set.insert curr visited) $ foldr (enqueue dist) q $ adjs curr

    enqueue dist c = Set.insert (dist + grid Map.! c, c)
    adjs (i, j) = filter (`Map.member` grid) [(i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)]

solve1 :: [[Int]] -> Int
solve1 xs = dikjstra (toMap xs) (0, 0) (length xs - 1, length (head xs) - 1)

solve2 :: [[Int]] -> Int
solve2 xs = dikjstra grid (0, 0) (5 * length xs - 1, 5 * length (head xs) - 1)
  where
    grid = toMap $ expand (map . addMod9) 5 $ map (expand addMod9 5) xs
    expand f n = concat . zipWith (map . f) [0 ..] . replicate n
    addMod9 idx x = (x + idx - 1) `mod` 9 + 1

parseInput :: String -> [[Int]]
parseInput = map (map (read . (: []))) . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
