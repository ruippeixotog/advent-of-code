import Lib.Intcode

gravity :: Int -> Int -> Prog -> Int
gravity a1 a2 = runProgMonad $ do
  writeData 1 a1
  writeData 2 a2
  runProg
  readData 0

solve1 :: Prog -> Int
solve1 = gravity 12 2

solve2 :: Prog -> Int
solve2 prog =
  let runs = [(a1, a2, gravity a1 a2 prog) | a1 <- [0 .. 99], a2 <- [0 .. 99]]
   in case filter (\(_, _, res) -> res == 19690720) runs of
        (a1, a2, _) : _ -> 100 * a1 + a2
        [] -> error "Noun-verb pair not found"

main :: IO ()
main = interact $ show . tee solve1 solve2 . parseProg
  where
    tee f1 f2 arg = (f1 arg, f2 arg)
