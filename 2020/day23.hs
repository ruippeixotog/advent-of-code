import Control.Arrow
import Data.IntMap.Strict (IntMap)
import qualified Data.IntMap.Strict as Map
import Data.List
import Data.Maybe
import Data.Sequence (Seq (..))
import qualified Data.Sequence as Seq

data CList = CList (IntMap (Seq Int)) (Seq Int)

cFromList :: [Int] -> CList
cFromList xs = CList Map.empty $ Seq.fromList xs

cPop :: CList -> (Int, CList)
cPop (CList aps Empty) = error $ "Empty list " <> show aps
cPop (CList aps (x :<| xs)) = case Map.lookup x aps of
  Just ap -> cPop (CList (Map.delete x aps) (x :<| ap Seq.>< xs))
  Nothing -> (x, CList aps xs)

cPopN :: Int -> CList -> ([Int], CList)
cPopN 0 cl = ([], cl)
cPopN n cl = case cPop cl of (x, cl') -> first (x :) $ cPopN (n - 1) cl'

cAppend :: Int -> CList -> CList
cAppend x (CList aps qs) = CList aps (qs :|> x)

cAppendAfter :: [Int] -> Int -> CList -> CList
cAppendAfter xs k (CList aps qs) = CList (Map.alter alterFunc k aps) qs
  where
    alterFunc = Just . (Seq.><) (Seq.fromList xs) . fromMaybe Empty

cToList :: CList -> [Int]
cToList (CList _ Empty) = []
cToList cl = case cPop cl of (x, cl') -> x : cToList cl'

play :: Int -> Int -> [Int] -> [Int]
play its n initials = move its $ cFromList $ initials ++ [length initials + 1 .. n]
  where
    move 0 cl = cToList cl
    move its' cl = case cPopN 4 cl of
      (x : seg, cl') -> move (its' - 1) $ cAppend x $ cAppendAfter seg (target x seg) cl'
      _ -> error "Illegal state"
    target x seg = case [x - 1, x - 2 .. 1] \\ seg of
      (prev : _) -> prev
      _ -> head $ [n, n - 1 .. 1] \\ seg

solve1 :: [Int] -> String
solve1 = concatMap show . take 8 . tail . dropWhile (/= 1) . cycle . play 100 9

solve2 :: [Int] -> Int
solve2 = product . take 2 . tail . dropWhile (/= 1) . cycle . play 10000000 1000000

input :: [Int]
input = [1, 3, 7, 8, 2, 6, 4, 9, 5]

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . const input
