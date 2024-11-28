# MiniDB

<pre>
Users Table:
id=1 name=Alice age=30
id=2 name=Bob age=25
id=3 name=Charlie age=35

Orders Table:
order_id=1 user_id=1 amount=50
order_id=2 user_id=2 amount=60
order_id=3 user_id=3 amount=70
order_id=4 user_id=1 amount=80

INNER JOIN:
age=30 id=1 name=Alice amount=50 order_id=1 user_id=1
age=30 id=1 name=Alice amount=80 order_id=4 user_id=1
age=25 id=2 name=Bob amount=60 order_id=2 user_id=2
age=35 id=3 name=Charlie amount=70 order_id=3 user_id=3

LEFT JOIN:
age=30 id=1 name=Alice amount=50 order_id=1 user_id=1
age=30 id=1 name=Alice amount=80 order_id=4 user_id=1
age=25 id=2 name=Bob amount=60 order_id=2 user_id=2
age=35 id=3 name=Charlie amount=70 order_id=3 user_id=3

RIGHT JOIN:
age=30 id=1 name=Alice amount=50 order_id=1 user_id=1
age=30 id=1 name=Alice amount=80 order_id=4 user_id=1
age=25 id=2 name=Bob amount=60 order_id=2 user_id=2
age=35 id=3 name=Charlie amount=70 order_id=3 user_id=3
age=30 id=1 name=Alice amount=50 order_id=1 user_id=1
age=25 id=2 name=Bob amount=60 order_id=2 user_id=2
age=35 id=3 name=Charlie amount=70 order_id=3 user_id=3
age=30 id=1 name=Alice amount=80 order_id=4 user_id=1

FULL OUTER JOIN:
age=30 id=1 name=Alice amount=50 order_id=1 user_id=1
age=30 id=1 name=Alice amount=80 order_id=4 user_id=1
age=25 id=2 name=Bob amount=60 order_id=2 user_id=2
age=35 id=3 name=Charlie amount=70 order_id=3 user_id=3
age=30 id=1 name=Alice amount=50 order_id=1 user_id=1
age=30 id=1 name=Alice amount=80 order_id=4 user_id=1
age=25 id=2 name=Bob amount=60 order_id=2 user_id=2
age=35 id=3 name=Charlie amount=70 order_id=3 user_id=3
age=30 id=1 name=Alice amount=50 order_id=1 user_id=1
age=25 id=2 name=Bob amount=60 order_id=2 user_id=2
age=35 id=3 name=Charlie amount=70 order_id=3 user_id=3
age=30 id=1 name=Alice amount=80 order_id=4 user_id=1
</pre>
