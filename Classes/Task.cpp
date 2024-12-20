#include "Task.h"

Task::Task(const std::string& description, int reward, int requiredCount)
    : description(description), reward(reward), requiredCount(requiredCount), currentProgress(0) {
}

void Task::updateProgress(int progress) {
    currentProgress += progress;
    if (currentProgress > requiredCount) {
        currentProgress = requiredCount;
    }
}

bool Task::isCompleted() const {
    return currentProgress >= requiredCount;
}

int Task::getReward() const {
    return reward;
}

std::string Task::getDescription() const {
    return description;
}
