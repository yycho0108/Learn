bmiTell :: (RealFloat a) => a -> a -> String
bmiTell weight height
	| bmi <= 18.5 = "UNDER"
	| bmi <= 25.0 = "PAR"
	| otherwise = "OVER"
    where bmi = weight / height^2


initials :: String -> String -> String
initials first last = [f] ++ "." ++ [l] ++ "."
 where (f:_) = first
       (l:_) = last


head' :: [a] -> a
head' l = case l of [] -> error "EMPTY"
                    (x:_) -> x

maximum' :: (Ord a) => [a] -> a
maximum' [] = error "EMPTY"
maximum' [x] = x
maximum' (x:xs)
    | x > curmax = x
    | otherwise = curmax
    where curmax = maximum' xs

replicate' n x
    | n <= 0 = []
    | otherwise = x:replicate' (n-1) x

take' n x
    | n <= 0 = []
    | otherwise = let (h:t) = x in h:(take' (n-1) t)

repeat' x = x:repeat' x

zip' :: [a] -> [b] -> [(a,b)]
zip' la lb
    | null la = []
    | null lb = []
    | otherwise = (ah,bh):zip' at bt
    where (ah:at) = la
          (bh:bt) = lb

zip'' :: [a] -> [b] -> [(a,b)]
zip'' _ [] = []
zip'' [] _ = []
zip'' (ah:at) (bh:bt) = (ah,bh):zip'' at bt

quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x:xs) =
    let smaller = quicksort [a | a <- xs, a <= x]
        bigger = quicksort [a | a <- xs, a > x]
    in smaller ++ [x] ++ bigger

biOp cmd a1 a2 
    | cmd == "A" = a1+a2 -- Addition
    | cmd == "S" = a1-a2 -- Subtraction
    | cmd == "D" = a1/a2 -- Division
    | cmd == "M" = a1*a2 -- Multiplication

add = biOp "A"
sub = biOp "S"
div = biOp "D"
mult = biOp "M"

e `elem'` l = if null [item |  item <- l, e == item]
    then False
    else True

forEach f l = [f(x) | x <- l]

zipWith' f la lb = [f a b | (a,b) <- zip la lb ]

flip' f y x = f x y
