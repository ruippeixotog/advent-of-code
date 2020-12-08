import Control.Arrow
import Data.Sequence (Seq)
import qualified Data.Sequence as Seq
import qualified Data.Set as Set
import Text.Regex

runProg :: Seq (String, Int) -> (Bool, Int)
runProg = runProg' Set.empty 0 0
  where
    runProg' visited pc acc prog
      | pc >= Seq.length prog = (True, acc)
      | pc `Set.member` visited = (False, acc)
      | otherwise =
        let next pc' acc' = runProg' (Set.insert pc visited) pc' acc' prog
         in case prog `Seq.index` pc of
              ("acc", a) -> next (pc + 1) (acc + a)
              ("jmp", a) -> next (pc + a) acc
              ("nop", _) -> next (pc + 1) acc
              (opcode, _) -> error $ "Illegal opcode: " <> opcode

solve1 :: Seq (String, Int) -> Int
solve1 = snd . runProg

solve2 :: Seq (String, Int) -> Int
solve2 prog = head $ map snd $ filter fst $ map (runProg . fixProg) [0 .. Seq.length prog - 1]
  where
    fixProg idx = Seq.adjust' fixInst idx prog
    fixInst ("nop", a) = ("jmp", a)
    fixInst ("jmp", a) = ("nop", a)
    fixInst inst = inst

parseInput :: String -> Seq (String, Int)
parseInput = Seq.fromList . map readInst . lines
  where
    readInst str =
      case matchRegex (mkRegex "([a-z]+) \\+?([-0-9]+)") str of
        Just [opcode, arg] -> (opcode, read arg)
        _ -> error $ "Invalid instruction: " <> str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
