import random
import time


class Task:
    def __init__(self, id: str, release_time: int, processing_time: int, delivery_time: int):
        self.id = id
        self.release_time = release_time
        self.processing_time = processing_time
        self.delivery_time = delivery_time

    def __repr__(self):
        return f"Task(id={self.id}, release_time={self.release_time}, processing_time={self.processing_time}, delivery_time={self.delivery_time})"
    def __str__(self):
        return f"Task(id={self.id}, release_time={self.release_time}, processing_time={self.processing_time}, delivery_time={self.delivery_time})"


class Dataset:
    def __init__(self, id: str, tasks: list[Task]):
        self.id = id
        self.tasks = tasks

    def __str__(self):
        ret_tasks = ""
        for task in self.tasks:
            ret_tasks += str(task)
        return f"Dataset(id={self.id}, tasks={ret_tasks})"

    def __repr__(self):
        ret_tasks = ""
        for task in self.tasks:
            ret_tasks += str(task)
        return f"Dataset(id={self.id}, tasks={ret_tasks})"

# function for creating a dataset from random values, input is the number of tasks
def create_dataset(n: int) -> Dataset:
    tasks = []
    for i in range(n):
        tasks.append(Task(str(i), random.randint(0, 100),
                     random.randint(1, 29), random.randint(1, 29)))
    return Dataset("data", tasks)

# measure time of function execution
def measure_time(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        return (result, end - start)
    return wrapper


def schrage(dataset: Dataset) -> tuple[str, int]:
    tasks = dataset.tasks
    sorted_tasks = sorted(tasks, key=lambda t: t.release_time)
    ready_queue, schedule = [], []
    time_, cmax = 0, 0
    while ready_queue or sorted_tasks:
        while sorted_tasks and sorted_tasks[0].release_time <= time_:
            ready_queue.append(sorted_tasks.pop(0))
        if not ready_queue:
            time_ = sorted_tasks[0].release_time
            continue
        task = max(ready_queue, key=lambda t: t.delivery_time)
        ready_queue.remove(task)
        schedule.append(task)
        time_ += task.processing_time
        cmax = max(cmax, time_ + task.delivery_time)
    return (dataset.id, cmax)


if __name__ == "__main__":

    tasks = [Task("1", 0, 3, 3), Task("2", 1, 2, 6), Task("3", 2, 1, 7)]

    dataset = Dataset("data", tasks)
    (res,t) = schrage(dataset)
    print(res, t)

    # # open results.csv file
    # with open("result.csv", "w") as file:

    #     for i in range(3, 10000):
    #         data = create_dataset(i)
    #         # print(data)
    #         (res, t) = measure_time(schrage)(data)
    #         file.write("%d; %f;\n" % (i, t))
    #         # print(f"{i}, {t}")
