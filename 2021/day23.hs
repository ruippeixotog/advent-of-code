import Control.Arrow
import Data.Char
import Data.Foldable
import qualified Data.HashMap.Strict as Map
import Data.Maybe
import Data.Sequence (Seq)
import qualified Data.Sequence as Seq

type State = (Seq (Maybe Int), Seq [Int])

step :: Int -> (State, Int) -> [(State, Int)]
step n ((spaces, rooms), cost) =
  catMaybes (zipWith moveIn [0 ..] $ toList spaces) ++ concat (zipWith moveOut [0 ..] $ toList rooms)
  where
    moveIn _ Nothing = Nothing
    moveIn idx (Just pod) =
      let room = rooms `Seq.index` pod
       in if any (/= pod) room || length (obstacles idx pod) > 1
            then Nothing
            else
              Just
                ( (Seq.update idx Nothing spaces, Seq.update pod (pod : room) rooms),
                  cost + 10 ^ pod * (abs (roomLoc pod - idx) + n - length room)
                )

    moveOut _ [] = []
    moveOut roomIdx room@(pod : rest) =
      if all (== roomIdx) room
        then []
        else
          mapMaybe
            ( \idx ->
                if isRoomLoc idx || not (null $ obstacles idx roomIdx)
                  then Nothing
                  else
                    Just
                      ( (Seq.update idx (Just pod) spaces, Seq.update roomIdx rest rooms),
                        cost + 10 ^ pod * (abs (roomLoc roomIdx - idx) + n - length rest)
                      )
            )
            [0 .. Seq.length spaces - 1]

    isRoomLoc idx = even idx && idx >= 2 && idx <= 8
    roomLoc roomIdx = 2 + roomIdx * 2

    obstacles idx roomIdx =
      let loc = roomLoc roomIdx
       in mapMaybe (spaces `Seq.index`) [min loc idx .. max loc idx]

calcCost :: Int -> State -> Int
calcCost n initial = snd $ head $ last $ takeWhile (not . null) $ iterate stepMemo [(initial, 0)]
  where
    stepMemo = Map.toList . Map.fromListWith min . concatMap (step n)

solve1 :: [[Int]] -> Int
solve1 m = calcCost 2 initial
  where
    initial =
      ( Seq.replicate 11 Nothing,
        Seq.fromList
          [ [m !! 2 !! 3, m !! 3 !! 3],
            [m !! 2 !! 5, m !! 3 !! 5],
            [m !! 2 !! 7, m !! 3 !! 7],
            [m !! 2 !! 9, m !! 3 !! 9]
          ]
      )

solve2 :: [[Int]] -> Int
solve2 m = calcCost 4 initial
  where
    initial =
      ( Seq.replicate 11 Nothing,
        Seq.fromList
          [ [m !! 2 !! 3, 3, 3, m !! 3 !! 3],
            [m !! 2 !! 5, 2, 1, m !! 3 !! 5],
            [m !! 2 !! 7, 1, 0, m !! 3 !! 7],
            [m !! 2 !! 9, 0, 2, m !! 3 !! 9]
          ]
      )

parseInput :: String -> [[Int]]
parseInput = map (map $ \ch -> ord ch - ord 'A') . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
