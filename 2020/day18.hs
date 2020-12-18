import Control.Arrow
import Data.Functor
import Text.Parsec
import Text.Parsec.Expr
import Text.Parsec.Language
import Text.Parsec.Token

parseAndEval :: [[(String, Int -> Int -> Int)]] -> String -> Int
parseAndEval ops = either (error . show) id . parse expr ""
  where
    expr = buildExpressionParser opTable term
    opTable = map (map $ uncurry binaryOp) ops
    binaryOp name fun = Infix (symbol lexer name $> fun) AssocLeft
    term = parens lexer expr <|> (fromInteger <$> natural lexer)
    lexer = makeTokenParser emptyDef

solve1 :: [String] -> Int
solve1 = sum . map (parseAndEval [[("+", (+)), ("*", (*))]])

solve2 :: [String] -> Int
solve2 = sum . map (parseAndEval [[("+", (+))], [("*", (*))]])

parseInput :: String -> [String]
parseInput = lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
