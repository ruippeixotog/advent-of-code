import Control.Arrow
import Data.Foldable
import Data.List.Split
import Data.Sequence (Seq (..))
import qualified Data.Sequence as Seq

hist :: [Int] -> Seq Int
hist = foldr (Seq.adjust (+ 1)) $ Seq.fromList $ replicate 9 0

step :: Seq Int -> Seq Int
step (zeros :<| rest) = Seq.adjust (+ zeros) 6 $ rest :|> zeros
step _ = error "Illegal state"

solve1 :: [Int] -> Int
solve1 = sum . toList . (!! 80) . iterate step . hist

solve2 :: [Int] -> Int
solve2 = sum . toList . (!! 256) . iterate step . hist

parseInput :: String -> [Int]
parseInput = map read . splitOn ","

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
