{-# LANGUAGE TupleSections #-}

import Control.Arrow
import Data.List
import Data.List.Split
import Text.Regex

type Tile = [[Char]]

variants :: Tile -> [Tile]
variants tile = [id, reverse] <*> take 4 (iterate rot90 tile)
  where
    rot90 = transpose . reverse

assemble :: [Tile] -> Tile
assemble = stripBorders . mergeAll
  where
    mergeAll [] = error "Illegal state"
    mergeAll [tile] = tile
    mergeAll (tile : rest) = case findMatching tile rest of
      Just (tile', rest') -> mergeAll (tile' : rest')
      Nothing -> mergeAll $ rest ++ [tile]

    findMatching _ [] = Nothing
    findMatching tile (tile' : rest) = case findMatchingVariant tile (variants tile') of
      Just merged -> Just (merged, rest)
      Nothing -> second (tile' :) <$> findMatching tile rest

    findMatchingVariant _ [] = Nothing
    findMatchingVariant tile (tile' : rest)
      | last tile == head tile' = Just $ init tile ++ tail tile'
      | last tile' == head tile = Just $ init tile' ++ tail tile
      | map last tile == map head tile' = Just $ zipWith (++) (map init tile) (map tail tile')
      | map last tile' == map head tile = Just $ zipWith (++) (map init tile') (map tail tile)
      | otherwise = findMatchingVariant tile rest

    stripBorders = map (init . tail) . init . tail

findMonsters :: Tile -> Int
findMonsters = length . filter isMonster . subtiles
  where
    subtiles = concatMap (transpose . tails . transpose) . tails
    isMonster (
      ( _ : _ :_:_: _ : _ : _ : _ :_:_: _ : _ : _ : _ :_:_: _ : _ :'#': _ :_) :
      ('#': _ :_:_: _ :'#':'#': _ :_:_: _ :'#':'#': _ :_:_: _ :'#':'#':'#':_) :
      ( _ :'#':_:_:'#': _ : _ :'#':_:_:'#': _ : _ :'#':_:_:'#': _ : _ : _ :_) : _) = True
    isMonster _ = False

solve1 :: [(Int, Tile)] -> Int
solve1 inp = product $ map fst $ filter ((== 2) . snd) $ map (uncurry connCount) inp
  where
    connCount tid = (tid,) . length . filter (connWithBorder tid) . borders
    connWithBorder tid b = any (connWithTile b . snd) $ filter ((/= tid) . fst) inp
    connWithTile border = any ((== border) . head) . variants
    borders tile = [head, last] <*> [tile, transpose tile]

solve2 :: [(Int, Tile)] -> Int
solve2 = minimum . map calmWaters . variants . assemble . map snd
  where
    calmWaters tile = countHashes tile - 15 * findMonsters tile
    countHashes = sum . map (length . filter (== '#'))

parseInput :: String -> [(Int, Tile)]
parseInput = map (parseTile . lines) . splitOn "\n\n"
  where
    parseTile (header : grid) =
      case matchRegex (mkRegex "Tile ([0-9]+):") header of
        Just [tileId] -> (read tileId, grid)
        _ -> error $ "Illegal tile header: " <> header
    parseTile _ = error "Empty tile"

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
