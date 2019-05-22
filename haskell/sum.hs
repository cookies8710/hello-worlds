#!/usr/bin/runhaskell

gn :: String -> IO Integer
gn msg = do
    putStrLn msg
    l <- getLine
    let i = read l :: Integer
    return i

pl1 :: IO (Integer -> Integer)
pl1 = return (+1)

main = do
    let m2 = gn "Insert n2"
    let m1 = gn "Insert n1"
    x <- (+) <$> m1 <*> m2
    putStrLn $ show x
    putStrLn "Done" 
