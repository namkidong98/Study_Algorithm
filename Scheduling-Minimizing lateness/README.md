## Scheduling: Minimizing Lateness
#### Goal: Find a schedule S so as to minimize the maximum lateness
#### lateness = max { 0, start + time spent - deadline } 
<br/>

#### Implementation
##### 1. job ID, time taken, deadline을 입력 받고 qsort를 통해 deadline이 적은 순으로 정렬한다
##### 2. deadline이 적은 순으로 job을 할당하며 lateness를 측정한다
##### 3. 모든 job이 할당되고 난 이후 maximum lateness를 측정한다

![lateness.png](https://github.com/namkidong98/Study_Algorithm/blob/main/Scheduling-Minimizing%20lateness/lateness.PNG)
