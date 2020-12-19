{-# LANGUAGE OverloadedStrings #-}

import Control.Arrow
import Data.Bifunctor
import Data.List.Split
import Data.Map (Map)
import qualified Data.Map.Merge.Strict as Map
import qualified Data.Map.Strict as Map
import Data.Maybe

data Rule = Prim Char | OrAnd [[Int]]

data Trie = Trie Bool (Map Char Trie)

tempty :: Trie
tempty = Trie False Map.empty

tadd :: Trie -> String -> Trie
tadd (Trie _ chs) [] = Trie True chs
tadd (Trie valid chs) (ch : rest) =
  Trie valid $ Map.alter (Just . flip tadd rest . fromMaybe tempty) ch chs

tmerge :: Trie -> Trie -> Trie
tmerge (Trie v1 chs1) (Trie v2 chs2) = Trie (v1 || v2) (merge' chs1 chs2)
  where
    merge' = Map.merge Map.preserveMissing Map.preserveMissing (Map.zipWithMatched $ const tmerge)

textend :: Trie -> Trie -> Trie
textend (Trie True chs1) t2 = tmerge (Trie False $ Map.map (`textend` t2) chs1) t2
textend (Trie False chs1) t2 = Trie False $ Map.map (`textend` t2) chs1

tconsume :: Trie -> String -> [String]
tconsume (Trie True chs) str = str : tconsume (Trie False chs) str
tconsume _ [] = []
tconsume (Trie False chs) (ch : rest) = maybe [] (`tconsume` rest) $ chs Map.!? ch

resolve :: Int -> Map Int Rule -> Trie
resolve root rules = computeMem Map.empty root Map.! root
  where
    computeMem acc ident
      | Map.member ident acc = acc
      | otherwise = uncurry (Map.insert ident) $ compute acc (rules Map.! ident)

    compute acc (Prim ch) = (tadd tempty [ch], acc)
    compute acc (OrAnd ors) = (flip computeOrs ors &&& id) $ foldl computeMem acc $ concat ors
    computeOrs acc = foldl tmerge tempty . map (computeAnds acc)
    computeAnds acc = foldl textend (tadd tempty "") . map (acc Map.!)

solve1 :: (Map Int Rule, [String]) -> Int
solve1 (rules, strs) = length $ filter (tcontains $ resolve 0 rules) strs
  where
    tcontains t str = "" `elem` tconsume t str

solve2 :: (Map Int Rule, [String]) -> Int
solve2 (rules, strs) = length $ filter (search42 (0 :: Int)) strs
  where
    trie42 = resolve 42 rules
    trie31 = resolve 31 rules
    search42 _ [] = False
    search42 n42 str = search31 n42 0 str || or (search42 (n42 + 1) <$> tconsume trie42 str)
    search31 n42 n31 [] = n31 > 0 && n42 > n31
    search31 n42 n31 str = or $ search31 n42 (n31 + 1) <$> tconsume trie31 str

parseInput :: String -> (Map Int Rule, [String])
parseInput = bimap (Map.fromList . map parseRule) tail . break null . lines
  where
    parseRule :: String -> (Int, Rule)
    parseRule str = case splitOn ": " str of
      [idStr, ['"', ch, '"']] -> (read idStr, Prim ch)
      [idStr, ors] -> (read idStr, OrAnd $ map (map read . words) $ splitOn " | " ors)
      _ -> error $ "Invalid rule: " <> str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
