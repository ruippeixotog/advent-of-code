import Control.Arrow
import qualified Data.HashMap.Strict as Map
import Data.List
import Data.List.Split
import Data.Maybe

type Coord = (Int, Int, Int)

type Scanner = [Coord]

cSub :: Coord -> Coord -> Coord
cSub (x1, y1, z1) (x2, y2, z2) = (x1 - x2, y1 - y2, z1 - z2)

variants :: Scanner -> [Scanner]
variants = nub . transpose . map variants'
  where
    variants' c = iterate ([id, rotX, rotY] <*>) [c] !! 6
    rotX (x, y, z) = (x, - z, y)
    rotY (x, y, z) = (z, y, - x)

match :: Scanner -> Scanner -> Maybe (Coord, Scanner)
match sc1 sc2 = fmap (id &&& merge) $ findTf $ [(cSub c2 c1, 1 :: Int) | c1 <- sc1, c2 <- sc2]
  where
    findTf = listToMaybe . Map.keys . Map.filter (>= 12) . Map.fromListWith (+)
    merge tf = nub $ sc1 ++ map (`cSub` tf) sc2

assemble :: [Scanner] -> ([Coord], Scanner)
assemble [] = error "Illegal state"
assemble [base] = ([(0, 0, 0)], base)
assemble (base : rest) =
  case findMatching rest of
    Just ((tf, sc'), rest') -> first (tf :) $ assemble (sc' : rest')
    Nothing -> assemble $ rest ++ [base]
  where
    findMatching [] = Nothing
    findMatching (sc' : rest') = case mapMaybe (match base) (variants sc') of
      (matched : _) -> Just (matched, rest')
      [] -> second (sc' :) <$> findMatching rest'

solve1 :: [Scanner] -> Int
solve1 = length . snd . assemble

solve2 :: [Scanner] -> Int
solve2 = maximum . dists . fst . assemble
  where
    dists cs = [norm $ cSub c2 c1 | c1 <- cs, c2 <- cs]
    norm (x, y, z) = abs x + abs y + abs z

parseInput :: String -> [Scanner]
parseInput = map (map parseCoord . tail . lines) . splitOn "\n\n"
  where
    parseCoord = (\[a, b, c] -> (a, b, c)) . map read . splitOn ","

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
