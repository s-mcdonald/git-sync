
/******************************************************************************
 * MIT License
 * 
 * Copyright (c) 2025 Sam McDonald
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * provided to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * -----------------------------------------------------------------------------
 * 
 * Author: Sam McDonald
 * Date: 2025-02-22
 * 
 * Description:
 * 
 * This program will sync a given branch with a remote
 * 
 *****************************************************************************/

#include <iostream>
#include <new> // Required for std::bad_alloc
#include <iomanip>
#include <git2.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "gr_lib.h"
#include "gr_io.h"
#include "gr_cli_options.h"
#include "gr_repo_state.h"
#include "sm_log.h"

// Global variables for tracking memory usage
static size_t s_total_memory_allocated = 0;
static int s_total_allocations = 0;
static int s_total_deallocations = 0;

#ifdef DEBUG
constexpr char* GITLIST_FAILED_INIT_LIBGIT2 = "Failed to initialize libgit2";
constexpr char* GITLIST_FAILED_OPEN_REPO = "Failed to open libgit2";
constexpr char* GITLIST_FAILED_CREATE_ITERATOR = "Failed to create branchiterator";

#else
constexpr char* GITLIST_FAILED_INIT_LIBGIT2 = "Unable to open repository.\n Please check that you are in the correct directory.\n";
constexpr char* GITLIST_FAILED_OPEN_REPO = GITLIST_FAILED_INIT_LIBGIT2;
constexpr char* GITLIST_FAILED_CREATE_ITERATOR = GITLIST_FAILED_INIT_LIBGIT2;

#endif


#ifdef DEBUG

void* operator new(std::size_t n) {
    s_total_memory_allocated += n;
    void* p = std::malloc(n);
    if (!p) {
        std::cerr << "Memory allocation failed" << std::endl;
        std::exit(EXIT_FAILURE); 
    }
    s_total_allocations++;
    return p;
}

void operator delete(void* p) noexcept {
    std::free(p);
    s_total_deallocations++;
}

void print_memory_usage() {
    std::cout 
        << "Total memory : ( " 
        << s_total_allocations 
        << " / "
        << s_total_deallocations
        << " )" 
        << " Total memory allocated/deallocated respectivly with Bytes:  " 
        << s_total_memory_allocated
        << std::endl;
}
#else
void print_memory_usage() {}
#endif
constexpr void print_usage() {
    // display output to terminal
}

int main(int argc, char* argv[]) 
{
    using namespace SamMcDonald;
    Log::set_log_level(LogLevel::LDEBUG);

#ifdef DEBUG
    std::cout << "DEBUG MODE:" << std::endl;
    std::cout << "" << std::endl;
#endif
 
    {
        const char * repo_path = "./";

        GitReal::Console console;

        if (git_libgit2_init() < 0) {
            Log::err(LogLevel::LERROR, GITLIST_FAILED_INIT_LIBGIT2);
            return -1;
        }

        git_repository *repo = nullptr;
        if (git_repository_open(&repo, repo_path) != 0) {
            git_libgit2_shutdown();
            Log::err(LogLevel::LWARNING, GITLIST_FAILED_OPEN_REPO);
            return -2;        
        }

        git_branch_iterator *iter = nullptr;
        if (git_branch_iterator_new(&iter, repo, GIT_BRANCH_LOCAL) != 0) {
            git_repository_free(repo);
            git_libgit2_shutdown();
            Log::err(LogLevel::LERROR, GITLIST_FAILED_CREATE_ITERATOR);
            return -4;
        }

        {
            // GitReal::BranchManager manager(repo, iter);
            // if (manager.is_porcelain() || manager.is_tracking_remote()) {
            //     // exit here with error
            // }

            // manager.sync();
        }

        git_branch_iterator_free(iter);
        git_repository_free(repo);
    }

#ifdef DEBUG
    print_memory_usage();
#endif
}
