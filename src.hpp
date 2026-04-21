# ifndef _SJTU_CPP_FINAL_SRC_HPP_
# define _SJTU_CPP_FINAL_SRC_HPP_

# include <vector>
# include <utility>

# ifndef _SJTU_CPP_FINAL_TASK_HPP_
# define _SJTU_CPP_FINAL_TASK_HPP_

typedef unsigned int uint;

namespace sjtu {
    // Description for each task:
    //   task_id: uint, unique for each task;
    //   priority: uint;
    //   time: uint, (remaining) time of the task.
    struct Task {
        uint task_id;
        uint priority;
        uint time;

        explicit Task(uint _task_id = 0, uint _priority = 0, uint _time = 0) {
            task_id = _task_id;
            priority = _priority;
            time = _time;
        }

        Task(const Task &rhs) {
            task_id = rhs.task_id;
            priority = rhs.priority;
            time = rhs.time;
        }

        ~ Task() = default;
    };

    // CPUState: idle and busy.
    enum CPUState {
        idle = 0, busy = 1
    };
}
# endif

# ifndef _SJTU_CPP_FINAL_CPU_HPP_
# define _SJTU_CPP_FINAL_CPU_HPP_

namespace sjtu {
    // CPU base class, modifications is not allowed.
    class CPU {
    protected:
        CPUState state;
        std::vector<Task> tasks;

    public:
        CPU() : tasks() {
            state = idle;
        }

        // Add a new task.
        int addTask(const Task &t) {
            tasks.push_back(t);
            return 1;
        }

        // Change the priority of one process, return 1 if success and return 0 if fail.
        int changePriority(uint task_id, uint priority) {
            for (auto &task: tasks)
                if (task.task_id == task_id) {
                    task.priority = priority;
                    return 1;
                }
            return 0;
        }

        virtual std::pair<CPUState, uint> run() = 0;

        virtual ~ CPU() = default;
    };
}
# endif

namespace sjtu {
    // FCFS method based CPU.
    class CPU_FCFS : public CPU {
    public:
        std::pair<CPUState, uint> run() override {
            for (auto &task : tasks) {
                if (task.time > 0) {
                    task.time--;
                    return std::make_pair(busy, task.task_id);
                }
            }
            return std::make_pair(idle, 0);
        }
    };

    // SRTF method based CPU.
    class CPU_SRTF : public CPU {
    public:
        std::pair<CPUState, uint> run() override {
            int best_idx = -1;
            uint min_time = 0xFFFFFFFF;

            for (int i = 0; i < (int)tasks.size(); ++i) {
                if (tasks[i].time > 0) {
                    if (best_idx == -1 || tasks[i].time < min_time) {
                        min_time = tasks[i].time;
                        best_idx = i;
                    }
                }
            }

            if (best_idx != -1) {
                tasks[best_idx].time--;
                return std::make_pair(busy, tasks[best_idx].task_id);
            }
            return std::make_pair(idle, 0);
        }
    };

    // priority method based CPU.
    class CPU_PRIORITY : public CPU {
    public:
        std::pair<CPUState, uint> run() override {
            int best_idx = -1;
            uint min_priority = 0xFFFFFFFF;

            for (int i = 0; i < (int)tasks.size(); ++i) {
                if (tasks[i].time > 0) {
                    if (best_idx == -1 || tasks[i].priority < min_priority) {
                        min_priority = tasks[i].priority;
                        best_idx = i;
                    }
                }
            }

            if (best_idx != -1) {
                tasks[best_idx].time--;
                return std::make_pair(busy, tasks[best_idx].task_id);
            }
            return std::make_pair(idle, 0);
        }
    };
}

# endif
