# GitHub Monorepo Splitter AI Agent

A Python-based AI agent that automatically splits a GitHub monorepo into multiple repositories, preserving git history for each project and common libraries.

## Features

- **Dual Mode Support**: 
  - **Branch Mode**: Extract different branches into separate repositories
  - **Project Mode**: Extract different projects from the same branch into separate repositories
- **Automatic Repository Creation**: Creates new GitHub repositories via API
- **History Preservation**: Maintains complete git history for each extracted project
- **Common Libraries**: Extracts shared code into a separate `common-libs` repository
- **AI-Powered Analysis**: Optional analysis to identify common files across projects
- **Dry Run Mode**: Test the process without making actual changes
- **Comprehensive Logging**: Detailed logs for debugging and monitoring

## Use Cases

### Branch Mode (Original)
For monorepos where different applications are on different branches:
```
monorepo/
├── frontend/ (on frontend branch)
├── backend/  (on backend branch)
├── mobile/   (on mobile branch)
└── shared/   (common libraries)
```

### Project Mode (New)
For monorepos where different projects are on the same main branch with shared libraries:
```
monorepo/
├── fractol/     (project 1)
├── printf/      (project 2)
├── pushswap/    (project 3)
├── libft/       (shared library)
└── other-files/
```

## Requirements

- Python 3.9+
- Git installed and available in PATH
- `git-filter-repo` installed and available in PATH
- GitHub Personal Access Token with repo scope

## Installation

1. **Clone or download this repository**

2. **Install Python dependencies**:
   ```bash
   pip install -r requirements.txt
   ```

3. **Install git-filter-repo**:
   ```bash
   # On macOS with Homebrew
   brew install git-filter-repo
   
   # On Ubuntu/Debian
   sudo apt-get install git-filter-repo
   
   # On Windows with Chocolatey
   choco install git-filter-repo
   
   # Or install via pip
   pip install git-filter-repo
   ```

4. **Configure the environment**:
   ```bash
   # The .env file is already created - edit it with your configuration
   nano .env
   # or
   code .env
   ```

## Configuration

The `.env` file is already created. Edit it with your configuration values:

### Required Variables

- `SOURCE_REPO_URL`: SSH or HTTPS URL of the monorepo to split
- `MODE`: Either `branch` or `project` (default: `branch`)
- `ORG`: GitHub organization or username to host the new repositories
- `GITHUB_TOKEN`: GitHub Personal Access Token with repo scope

### Mode-Specific Variables

#### Branch Mode
- `BRANCHES`: Comma-separated list of branch names (each becomes a separate app)

#### Project Mode
- `PROJECTS`: Comma-separated list of project directory names (each becomes a separate app)

### Optional Variables

- `COMMON_PATH`: Path to common libraries folder (extracted to `common-libs` repo)
- `OPENAI_API_KEY`: OpenAI API key for AI-powered common file analysis

### Example Configurations

#### Branch Mode Configuration
```env
# Monorepo to split (SSH or HTTPS URL)
SOURCE_REPO_URL=git@github.com:mycompany/monorepo.git

# Mode: branch-based splitting
MODE=branch

# Comma-separated list of branch names (apps)
BRANCHES=frontend,backend,mobile,admin,api

# Path for common libraries inside the repo (optional)
COMMON_PATH=shared/

# GitHub organization or username to create new repos under
ORG=mycompany

# GitHub Personal Access Token with repo scope
GITHUB_TOKEN=ghp_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
```

#### Project Mode Configuration
```env
# Monorepo to split (SSH or HTTPS URL)
SOURCE_REPO_URL=git@github.com:mycompany/monorepo.git

# Mode: project-based splitting
MODE=project

# Comma-separated list of project directories
PROJECTS=fractol,printf,pushswap

# Path for common libraries inside the repo (optional)
COMMON_PATH=libft

# GitHub organization or username to create new repos under
ORG=mycompany

# GitHub Personal Access Token with repo scope
GITHUB_TOKEN=ghp_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
```

## Usage

### Quick Start

1. **Test your configuration**:
   ```bash
   python test_config.py
   ```

2. **Dry Run (Test Mode)**:
   ```bash
   # For branch mode
   python split_repo_agent.py --dry-run --mode branch
   
   # For project mode
   python split_repo_agent.py --dry-run --mode project
   ```

3. **Actual Execution**:
   ```bash
   # For branch mode
   python split_repo_agent.py --mode branch
   
   # For project mode
   python split_repo_agent.py --mode project
   ```

### Programmatic Usage

You can also use the agent programmatically:

```python
from split_repo_agent import RepoSplitter, RepoSplitterConfig

# Branch mode example
config = RepoSplitterConfig(
    source_repo_url="git@github.com:org/monorepo.git",
    mode="branch",
    branches=["app1", "app2", "app3"],
    common_path="shared/",
    org="my-org",
    github_token="ghp_xxx",
    dry_run=False
)

# Project mode example
config = RepoSplitterConfig(
    source_repo_url="git@github.com:org/monorepo.git",
    mode="project",
    projects=["fractol", "printf", "pushswap"],
    common_path="libft",
    org="my-org",
    github_token="ghp_xxx",
    dry_run=False
)

with RepoSplitter(config) as splitter:
    splitter.split_repositories()
```

### Example Output

#### Branch Mode Output
```
2024-01-15 10:30:00 - INFO - Configuration loaded: mode=branch, org: mycompany
2024-01-15 10:30:01 - INFO - Cloning source repository: git@github.com:mycompany/monorepo.git
2024-01-15 10:30:05 - INFO - Analyzing for common files...
2024-01-15 10:30:06 - INFO - Found 15 common files across all branches
2024-01-15 10:30:07 - INFO - Processing branch: frontend
2024-01-15 10:30:08 - INFO - Created repository: frontend-app
2024-01-15 10:30:12 - INFO - Successfully extracted branch 'frontend' to 'frontend-app'
2024-01-15 10:30:12 - INFO - Repository URL: https://github.com/mycompany/frontend-app.git
```

#### Project Mode Output
```
2024-01-15 10:30:00 - INFO - Configuration loaded: mode=project, org: mycompany
2024-01-15 10:30:01 - INFO - Cloning source repository: git@github.com:mycompany/monorepo.git
2024-01-15 10:30:05 - INFO - Analyzing for common files...
2024-01-15 10:30:06 - INFO - Found 5 common files across all projects
2024-01-15 10:30:07 - INFO - Processing project: fractol
2024-01-15 10:30:08 - INFO - Created repository: fractol-app
2024-01-15 10:30:12 - INFO - Successfully extracted project 'fractol' to 'fractol-app'
2024-01-15 10:30:12 - INFO - Repository URL: https://github.com/mycompany/fractol-app.git
```

## How It Works

### 1. Repository Cloning
- Clones the source monorepo as a mirror to preserve all history
- Uses temporary directories for processing

### 2. Branch Mode Extraction
For each branch in the `BRANCHES` configuration:
- Creates a new GitHub repository via API
- Extracts only that branch's history
- Renames the branch to `main`
- Pushes the complete history to the new repository

### 3. Project Mode Extraction
For each project in the `PROJECTS` configuration:
- Creates a new GitHub repository via API
- Uses `git filter-repo` to extract only files from the specified project directory
- Preserves history for the extracted files
- Pushes the complete history to the new repository

### 4. Common Libraries Extraction
If `COMMON_PATH` is specified:
- Uses `git filter-repo` to extract only files from the specified path
- Creates a `common-libs` repository
- Preserves history for the extracted files

### 5. AI Analysis (Optional)
- Analyzes file trees across all branches/projects
- Identifies common files that might be candidates for shared libraries
- Provides suggestions for what could be moved to `COMMON_PATH`

## Repository Structure

### After Branch Mode Splitting
```
mycompany/
├── frontend-app/     # Extracted from frontend branch
├── backend-app/      # Extracted from backend branch
├── mobile-app/       # Extracted from mobile branch
├── admin-app/        # Extracted from admin branch
├── api-app/          # Extracted from api branch
└── common-libs/      # Extracted from COMMON_PATH
```

### After Project Mode Splitting
```
mycompany/
├── fractol-app/      # Extracted from fractol/ directory
├── printf-app/       # Extracted from printf/ directory
├── pushswap-app/     # Extracted from pushswap/ directory
└── common-libs/      # Extracted from libft/ directory
```

## Project Structure

```
aiAgent/
├── split_repo_agent.py    # Main agent script
├── test_config.py         # Configuration validation script
├── example_usage.py       # Programmatic usage example
├── requirements.txt       # Python dependencies
├── .env                   # Configuration file (edit this)
├── .gitignore            # Git ignore rules
└── README.md             # This documentation
```

## Error Handling

The agent includes comprehensive error handling:

- **Validation**: Checks all required configuration variables
- **Git Operations**: Handles git command failures gracefully
- **GitHub API**: Manages API rate limits and authentication errors
- **Cleanup**: Automatically removes temporary files on completion or error
- **Logging**: Detailed logs saved to `repo_splitter.log`

## Security Considerations

- **GitHub Token**: Use a Personal Access Token with minimal required scopes (`repo` scope)
- **SSH Keys**: Ensure SSH keys are properly configured for private repositories
- **Temporary Files**: All temporary files are automatically cleaned up
- **Dry Run**: Always test with `--dry-run` first
- **Environment File**: Never commit `.env` file to version control (it's already in `.gitignore`)

## Troubleshooting

### Common Issues

1. **GitHub API Rate Limits**
   - The agent handles rate limits automatically
   - Consider using a GitHub App token for higher limits

2. **SSH Authentication**
   - Ensure SSH keys are added to your GitHub account
   - Test SSH connection: `ssh -T git@github.com`

3. **git-filter-repo Not Found**
   - Install git-filter-repo: `pip install git-filter-repo`
   - Ensure it's available in your PATH

4. **Permission Denied**
   - Verify GitHub token has `repo` scope
   - Check organization permissions if creating repos in an org

5. **Project Not Found (Project Mode)**
   - Ensure project directories exist in the repository
   - Check that `PROJECTS` variable contains valid directory names

### Debug Mode

Enable debug logging by modifying the script:

```python
logging.basicConfig(level=logging.DEBUG, ...)
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Support

For issues and questions:
1. Check the troubleshooting section
2. Review the logs in `repo_splitter.log`
3. Run `python test_config.py` to validate your setup
4. Create an issue with detailed error information

## Next Steps

After setting up your configuration:

1. **Edit `.env`** with your actual values
2. **Run `python test_config.py`** to validate everything
3. **Test with `python split_repo_agent.py --dry-run --mode project`**
4. **Execute with `python split_repo_agent.py --mode project`**

The agent will create repositories based on your mode:
- **Branch Mode**: One repository per branch + common-libs (if specified)
- **Project Mode**: One repository per project + common-libs (if specified)
