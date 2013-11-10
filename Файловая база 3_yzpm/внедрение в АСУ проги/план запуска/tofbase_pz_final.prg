**clear
s=sqlconnect('skb35','oasu','oasu')
if s>0 then
	k=sqlexe(s,"Call oasu.Finalize_Sending()")
	s=sqldisconnect(s)
endif
