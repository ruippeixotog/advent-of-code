{-# LANGUAGE TupleSections #-}

import Control.Arrow
import qualified Data.HashMap.Strict as Map
import Text.Regex

type Coord = (Int, Int)

solve1 :: [(Coord, Coord)] -> Int
solve1 = solve2 . filter isValid
  where
    isValid ((x0, y0), (x1, y1)) = x0 == x1 || y0 == y1

solve2 :: [(Coord, Coord)] -> Int
solve2 = Map.size . Map.filter (> 1) . hist . concatMap expand
  where
    expand ((x0, y0), (x1, y1)) = range x0 x1 `zip` range y0 y1
    range p0 p1 = [p0, p0 + signum (p1 - p0) .. p1]
    hist = Map.fromListWith (+) . map (,1)

parseInput :: String -> [(Coord, Coord)]
parseInput = map parseLine . lines
  where
    parseLine str =
      case matchRegex (mkRegex "([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)") str of
        Just [x0, y0, x1, y1] -> ((read x0, read y0), (read x1, read y1))
        _ -> error $ "Invalid line: " <> show str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
