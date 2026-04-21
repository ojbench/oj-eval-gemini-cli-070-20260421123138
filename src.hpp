# ifndef _SJTU_CPP_FINAL_SRC_HPP_
# define _SJTU_CPP_FINAL_SRC_HPP_

namespace sjtu {

    // FCFS method based CPU.
    class CPU_FCFS : public CPU {
    public:
        pair<CPUState, uint> run() override {
            for (auto &task : tasks) {
                if (task.time > 0) {
                    task.time--;
                    return make_pair(busy, task.task_id);
                }
            }
            return make_pair(idle, 0);
        }
    };

    // SRTF method based CPU.
    class CPU_SRTF : public CPU {
    public:
        pair<CPUState, uint> run() override {
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
                return make_pair(busy, tasks[best_idx].task_id);
            }
            return make_pair(idle, 0);
        }
    };

    // priority method based CPU.
    class CPU_PRIORITY : public CPU {
    public:
        pair<CPUState, uint> run() override {
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
                return make_pair(busy, tasks[best_idx].task_id);
            }
            return make_pair(idle, 0);
        }
    };
}

# endif
