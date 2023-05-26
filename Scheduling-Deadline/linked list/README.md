## Scheduling: Deadline_linked list
#### Goal: schedule the jobs so as to maximize the total profit
#### not all jobs have to be sheduled
<br/>

#### Implementation - Linked list
##### 1. job ID, time taken, deadline을 입력 받고 qsort를 통해 profit이 큰 순으로 정렬한다
##### 2. profit이 큰 순서대로 n개의 job을 탐색하면서 Linked list에 추가될 수 있는지 없는지 판단한다
##### 3. 기존에 만들어진 Linked List를 탐색하여 새로 추가될 노드의 deadline이 작은 위치에 추가될 수 있다
##### 4. 그러나 해당 노드를 추가했을 때 Linked List의 노드들 중 하나라도 deadline을 초과하는 경우에는 해당 추가될 수 없다 
##### 5. 이런 원리로 n개의 job에 대해 추가 여부를 판단하여 Linked List를 구성하고 결과를 출력한다

![deadline.png](https://github.com/namkidong98/Study_Algorithm/blob/main/Scheduling-Deadline/linked%20list/deadline.PNG)
