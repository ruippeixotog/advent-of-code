import Control.Arrow
import Control.Monad
import Control.Monad.State.Strict
import Data.Foldable
import Data.Ix
import Data.Maybe
import Data.Sequence (Seq (..))
import qualified Data.Sequence as Seq

type GridState a = State (Seq (Seq Char)) a

bounds :: Seq (Seq Char) -> ((Int, Int), (Int, Int))
bounds grid@(row :<| _) = ((0, 0), (Seq.length grid - 1, Seq.length row - 1))
bounds _ = error "Empty grid"

cell :: (Int, Int) -> GridState Char
cell (i, j) = (`Seq.index` j) . (`Seq.index` i) <$> get

putCell :: (Int, Int) -> Char -> GridState ()
putCell (i, j) val = put . Seq.adjust (Seq.update j val) i =<< get

isValid :: (Int, Int) -> GridState Bool
isValid pos = flip inRange pos . bounds <$> get

line :: (Int, Int) -> (Int, Int) -> GridState [Char]
line (i, j) (di, dj) = do
  valid <- isValid (i + di, j + dj)
  if valid
    then (:) <$> cell (i + di, j + dj) <*> line (i + di, j + dj) (di, dj)
    else return []

simulate :: Int -> ([Char] -> Maybe Char) -> GridState ()
simulate occ adjSel = do
  grid <- get
  let positions = range $ bounds grid
  newCells <- sequence $ newCell <$> positions
  zipWithM_ putCell positions newCells
  newGrid <- get
  when (grid /= newGrid) $ simulate occ adjSel
  where
    dirs = [(0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1), (1, 0), (1, 1)]
    newCell pos = do
      curr <- cell pos
      adjs <- mapMaybe adjSel <$> sequence [line pos dir | dir <- dirs]
      return $ case (curr, length $ filter (== '#') adjs) of
        ('L', 0) -> '#'
        ('#', n) -> if n >= occ then 'L' else '#'
        (ch, _) -> ch

occupiedCount :: GridState Int
occupiedCount = sum . fmap (length . Seq.filter (== '#')) <$> get

solve1 :: Seq (Seq Char) -> Int
solve1 = evalState $ simulate 4 listToMaybe >> occupiedCount

solve2 :: Seq (Seq Char) -> Int
solve2 = evalState $ simulate 5 (find (/= '.')) >> occupiedCount

parseInput :: String -> Seq (Seq Char)
parseInput = Seq.fromList . map Seq.fromList . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
