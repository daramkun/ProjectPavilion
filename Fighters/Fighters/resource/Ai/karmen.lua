--Karmen AI File

if (P1_GetX() - P2_GetX() >= 150) then
	P2_SetState(P2_GetDir(), 1)
	P2_SetX(P2_GetX() - 4)
end

if (P2_GetX() - P1_GetX() >= 150) then
	P2_SetState(P2_GetDir(), 1)
	P2_SetX(P2_GetX() - 4)
end

if (P2_GetX() - P1_GetX() < 150) then
	if(P1_GetArtipect(1) > 0) then
		if(Random(0, 2) == 1) then
			P2_SetState(P2_GetDir(), 2);
		else
			P2_SetState(P2_GetDir(), 3);
		end
	elseif(P1_GetArtipect(2) > 0) then
		P2_SetState(P2_GetDir(), 4);
	end
end