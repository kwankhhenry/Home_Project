#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip> // For formatting output

constexpr int GRID_SIZE = 5; // 5x5 grid
constexpr double ALPHA = 0.1; // Learning rate
constexpr double GAMMA = 0.9; // Discount factor
constexpr double EPSILON = 0.1; // Exploration rate
constexpr int EPISODES = 1000;
constexpr int MAX_STEPS = 100;
constexpr double REWARD_GOAL = 10.0;
constexpr double PENALTY_STEP = -1.0;

// Actions: 0 = UP, 1 = DOWN, 2 = LEFT, 3 = RIGHT
enum Actions { UP, DOWN, LEFT, RIGHT };

// Environment class
class Environment {
public:
    Environment() : agent_x(0), agent_y(0) {}

    void reset() {
        agent_x = 0;
        agent_y = 0;
    }

    std::pair<int, int> get_state() const {
        return {agent_x, agent_y};
    }

    bool is_goal() const {
        return agent_x == GRID_SIZE - 1 && agent_y == GRID_SIZE - 1;
    }

    double step(int action) {
        int new_x = agent_x;
        int new_y = agent_y;

        if (action == UP && agent_x > 0) new_x--;
        if (action == DOWN && agent_x < GRID_SIZE - 1) new_x++;
        if (action == LEFT && agent_y > 0) new_y--;
        if (action == RIGHT && agent_y < GRID_SIZE - 1) new_y++;

        agent_x = new_x;
        agent_y = new_y;

        if (is_goal()) return REWARD_GOAL;
        return PENALTY_STEP;
    }

private:
    int agent_x;
    int agent_y;
};

// Q-Learning agent
class Agent {
public:
    Agent() {
        q_table.resize(GRID_SIZE, std::vector<std::vector<double>>(GRID_SIZE, std::vector<double>(4, 0.0)));
    }

    void train(Environment& env) {
        for (int episode = 0; episode < EPISODES; ++episode) {
            env.reset();
            auto state = env.get_state();
            for (int step = 0; step < MAX_STEPS; ++step) {
                int action = choose_action(state);
                double reward = env.step(action);
                auto next_state = env.get_state();
                update_q_table(state, action, reward, next_state);
                state = next_state;

                if (env.is_goal()) break;
            }
        }
    }

    void test(Environment& env) {
        env.reset();
        auto state = env.get_state();
        int steps = 0;
        while (!env.is_goal() && steps < MAX_STEPS) {
            int action = best_action(state);
            env.step(action);
            state = env.get_state();
            ++steps;
            std::cout << "Step " << steps << ": " << "Agent at (" << state.first << ", " << state.second << ")\n";
        }

        if (env.is_goal())
            std::cout << "Agent reached the goal in " << steps << " steps!\n";
        else
            std::cout << "Agent failed to reach the goal.\n";
    }

private:
    std::vector<std::vector<std::vector<double>>> q_table;

    int choose_action(const std::pair<int, int>& state) {
        if ((double)rand() / RAND_MAX < EPSILON) {
            return rand() % 4; // Explore
        }
        return best_action(state); // Exploit
    }

    int best_action(const std::pair<int, int>& state) {
        const auto& actions = q_table[state.first][state.second];
        return std::distance(actions.begin(), std::max_element(actions.begin(), actions.end()));
    }

    void update_q_table(const std::pair<int, int>& state, int action, double reward, const std::pair<int, int>& next_state) {
        double max_future_q = *std::max_element(q_table[next_state.first][next_state.second].begin(), q_table[next_state.first][next_state.second].end());
        double current_q = q_table[state.first][state.second][action];
        q_table[state.first][state.second][action] = current_q + ALPHA * (reward + GAMMA * max_future_q - current_q);
    }
};

int main() {
    srand((unsigned)time(0));
    Environment env;
    Agent agent;

    std::cout << "Training agent...\n";
    agent.train(env);

    std::cout << "\nTesting agent...\n";
    agent.test(env);

    return 0;
}