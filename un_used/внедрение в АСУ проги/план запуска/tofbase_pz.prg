**clear
s=sqlconnect('skb35','oasu','oasu')
if s>0 then
	k=sqlexe(s,"Call oasu.Clear_Incoming()")
	**?k
	select Planz
	scan
		_sql="Call oasu.Send_Plan_Row("+[']+Planz.Zak+[',']+Planz.Pt+[',']+Planz.Obi+[',']+STR(Planz.kol,10,5)+[']+")"
		**?_sql
		k=sqlexe(s,_sql)
		**?k
	endscan
	
	select Poli
	scan
		_sql="Call oasu.Send_Poli_Row("+[']+Poli.Obi+[',']+Poli.Obu+[',']+Poli.Obd+[',']+STR(Poli.kol,10,5)+[',']+STR(Poli.kolp,17,5)+[',']+Poli.ei+[']+")"
		**?_sql
		k=sqlexe(s,_sql)
		**?k
	endscan	
	
	s=sqldisconnect(s)
endif
