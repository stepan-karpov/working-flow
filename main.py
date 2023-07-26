import time

def progress_bar(iteration, total, bar_length=50):
    progress = (iteration / total)
    arrow = '=' * int(round(progress * bar_length) - 1)
    spaces = ' ' * (bar_length - len(arrow))
    print(f'\rProgress: [{arrow}{spaces}] {int(progress * 100)}%', end='', flush=True)

# Example usage:
total_iterations = 100
for i in range(total_iterations):
    # Simulating some work being done
    time.sleep(0.1)

    # Update the progress bar
    progress_bar(i + 1, total_iterations)

print()  # Move to the next line after the progress bar is completed