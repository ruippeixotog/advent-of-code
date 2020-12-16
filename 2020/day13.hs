{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE TupleSections #-}

import Control.Arrow
import Data.Maybe
import qualified Data.Text as T
import Text.Read

solve1 :: (Int, [(Int, Int)]) -> Int
solve1 (n, schs) = uncurry (*) $ minimum $ map ((waitTime &&& id) . snd) schs
  where
    waitTime sch = sch - n `mod` sch

solve2 :: (Int, [(Int, Int)]) -> Int
solve2 (_, schs) = sync 0 1 schs
  where
    sync t _ [] = t
    sync t delta schs'@((i, sch) : rest)
      | (t + i) `mod` sch == 0 = sync t (delta * sch) rest
      | otherwise = sync (t + delta) delta schs'

parseInput :: String -> (Int, [(Int, Int)])
parseInput str =
  case lines str of
    [n, schs] -> (read n, readSchs schs)
    _ -> error $ "Illegal input: " <> str
  where
    split = map T.unpack . T.splitOn "," . T.pack
    readSchs = mapMaybe (\(i, sch) -> (i,) <$> readMaybe sch) . zip [0 ..] . split

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
