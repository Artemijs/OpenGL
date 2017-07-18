import subprocess

print subprocess.check_output("git add --all", shell = True)
print subprocess.check_output("git commit -m'testing auto pushing'",shell = True);
print subprocess.check_output("git push", shell = True)

