import Control.Arrow
import Data.Foldable
import Data.List.Split
import Data.Set (Set)
import qualified Data.Set as Set

solve1 :: [[Set Char]] -> Int
solve1 = sum . map (length . fold)

solve2 :: [[Set Char]] -> Int
solve2 = sum . map (length . foldr1 Set.intersection)

parseInput :: String -> [[Set Char]]
parseInput = map (map Set.fromList . words) . splitOn "\n\n"

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
