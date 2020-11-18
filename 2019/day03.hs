import Control.Arrow
import qualified Data.Map.Strict as M
import qualified Data.Set as S

data Dir = U | D | L | R deriving (Read, Show)

type Path = [(Dir, Int)]

expandPath :: (Int, Int) -> Path -> [(Int, Int)]
expandPath _ [] = []
expandPath curr ((_, 0) : rest) = expandPath curr rest
expandPath (x, y) ((dir, k) : rest) =
  let next = case dir of
        U -> (x, y - 1)
        D -> (x, y + 1)
        L -> (x - 1, y)
        R -> (x + 1, y)
   in next : expandPath next ((dir, k - 1) : rest)

solve1 :: (Path, Path) -> Int
solve1 (p1, p2) =
  let p1' = S.fromList $ expandPath (0, 0) p1
      p2' = S.fromList $ expandPath (0, 0) p2
   in S.findMin $ S.map (\(x, y) -> abs x + abs y) $ S.intersection p1' p2'

solve2 :: (Path, Path) -> Int
solve2 (p1, p2) =
  let p1' = M.fromList $ reverse $ (`zip` [1 ..]) $ expandPath (0, 0) p1
      p2' = M.fromList $ reverse $ (`zip` [1 ..]) $ expandPath (0, 0) p2
   in minimum $ M.elems $ M.intersectionWith (+) p1' p2'

parseInput :: String -> (Path, Path)
parseInput str =
  let [p1, p2] = map parsePath $ lines str
   in (p1, p2)
  where
    parsePath "" = []
    parsePath str' =
      case break (== ',') str' of
        (dir : n, ',' : rest) -> (read $ dir : [], read n) : parsePath rest
        (dir : n, "") -> [(read $ dir : [], read n)]
        _ -> error "Malformed input"

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
