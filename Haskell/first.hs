doubleMe x = x + x
doubleUs x y = doubleMe x + doubleMe y
smaller x y = if x<y then x else y
doubleSmaller x y = 2*(smaller x y)

factorial :: (Integral a) => a -> a
factorial 0 = 1
factorial n = n * factorial (n-1)


charName :: Char -> String
charName 'a' = "ALBERT"


--dot :: (Num a) => [a] -> [a] -> [a]
dot a b = [c*d | (c,d) <- zip a b]

--printf [] = show ""
--printf head:rest = show head printf rest
conc :: [[Char]] -> [Char]
conc [] = ""
conc (head:rest) = head ++ concat(rest)

water :: (RealFloat a) => a -> String
water t
	| t <= 0.0 = "ICE"
	| t <= 100.0 = "WATER"
	| True = "VAPOR"

getE :: (RealFloat x) => x -> x
getE x = (1.0 + 1.0/x)**x
