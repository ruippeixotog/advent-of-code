import Control.Arrow
import Data.Sequence (Seq)
import qualified Data.Sequence as Seq

countTrees :: Int -> Int -> Seq (Seq Char) -> Int
countTrees r d grid = length $ filter (== '#') $ zipWith isTree rows cols
  where
    rowSize = Seq.length grid
    colSize = Seq.length $ Seq.index grid 0
    rows = [0, d .. rowSize - 1]
    cols = map (`mod` colSize) [0, r ..]
    isTree row col = grid `Seq.index` row `Seq.index` col

solve1 :: Seq (Seq Char) -> Int
solve1 = countTrees 3 1

solve2 :: Seq (Seq Char) -> Int
solve2 = product . mapM (uncurry countTrees) [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]

parseInput :: String -> Seq (Seq Char)
parseInput = Seq.fromList . map Seq.fromList . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
