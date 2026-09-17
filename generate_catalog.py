#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
generate_catalog.py
自动扫描 22408_2027 仓库各科目笔记，生成用于前端静态门户 (index.html) 的目录结构数据 catalog.js。
"""

import os
import re
import json

# 需要忽略的文件夹和文件
IGNORE_DIRS = {
    '.git', '.idea', '.agents', '.gemini', 'build', 'cmake-build-debug',
    'node_modules', '__pycache__', 'camera', 'assets'
}
IGNORE_FILES = {
    'desktop.ini', '.DS_Store', 'CMakeLists.txt', 'gen_CMake.py',
    'catalog.js', 'catalog.json', 'generate_catalog.py'
}

# 根目录文件展示顺序
ROOT_DOCS = [
    {"name": "备考核心总纲与录取档案", "path": "NOTICE.md", "icon": "fa-compass"},
    {"name": "仓库主页全景说明", "path": "README.md", "icon": "fa-book-open"}
]

# 科目配置及图标/主题色
SUBJECT_CONFIG = {
    "DailyPlan": {
        "icon": "fa-calendar-check",
        "badge": "每日计划与复盘",
        "color": "#ec4899"
    },
    "101 思想政治": {
        "icon": "fa-landmark-flag",
        "badge": "公共课",
        "color": "#ef4444"
    },
    "201 英语一": {
        "icon": "fa-language",
        "badge": "英语一",
        "color": "#10b981"
    },
    "302 数学二": {
        "icon": "fa-square-root-variable",
        "badge": "重点核心",
        "color": "#8b5cf6"
    },
    "自命题 数据科学基础": {
        "icon": "fa-database",
        "badge": "自命题专业课",
        "color": "#06b6d4"
    },
    "备用": {
        "icon": "fa-box-archive",
        "badge": "备用资料库",
        "color": "#64748b"
    },
    "204 英语二": {
        "icon": "fa-book",
        "badge": "历史储备",
        "color": "#64748b"
    },
    "Leetcode": {
        "icon": "fa-code",
        "badge": "代码手撕",
        "color": "#f59e0b"
    }
}

VALID_EXTENSIONS = {'.html', '.pdf', '.md'}

def natural_sort_key(s):
    """自然排序算法，支持 Chap1, Chap2, Chap10 正确排序"""
    return [int(text) if text.isdigit() else text.lower() for text in re.split(r'(\d+)', str(s))]

def get_file_type(ext):
    ext = ext.lower()
    if ext == '.html':
        return 'html'
    elif ext == '.pdf':
        return 'pdf'
    elif ext == '.md':
        return 'md'
    return 'other'

def scan_directory(dir_path, rel_path=""):
    """
    递归扫描目录，将同一文件名前缀的 .html / .pdf / .md 聚合为一个复合条目
    """
    entries = []
    try:
        items = os.listdir(dir_path)
    except Exception as e:
        print(f"Error reading {dir_path}: {e}")
        return entries

    # 分离子文件夹和文件
    subdirs = []
    doc_groups = {} # base_name -> dict(html=..., pdf=..., md=...)

    for item in items:
        if item in IGNORE_DIRS or item in IGNORE_FILES:
            continue
        full_p = os.path.join(dir_path, item)
        curr_rel = os.path.join(rel_path, item).replace('\\', '/')

        if os.path.isdir(full_p):
            subdirs.append((item, full_p, curr_rel))
        elif os.path.isfile(full_p):
            name, ext = os.path.splitext(item)
            ext_lower = ext.lower()
            if ext_lower in VALID_EXTENSIONS:
                if name not in doc_groups:
                    doc_groups[name] = {}
                doc_groups[name][get_file_type(ext_lower)] = curr_rel

    # 递归子目录
    subdirs.sort(key=lambda x: natural_sort_key(x[0]))
    for sub_name, sub_full, sub_rel in subdirs:
        children = scan_directory(sub_full, sub_rel)
        if children: # 仅保留非空子目录
            entries.append({
                "type": "folder",
                "name": sub_name,
                "path": sub_rel,
                "children": children
            })

    # 处理聚合文件
    sorted_doc_names = sorted(doc_groups.keys(), key=natural_sort_key)
    for doc_name in sorted_doc_names:
        formats = doc_groups[doc_name]
        # 确定默认展示格式：优先 HTML，其次 PDF，再次 MD
        if 'html' in formats:
            default_fmt = 'html'
            default_path = formats['html']
        elif 'pdf' in formats:
            default_fmt = 'pdf'
            default_path = formats['pdf']
        else:
            default_fmt = 'md'
            default_path = formats['md']

        entries.append({
            "type": "doc",
            "name": doc_name,
            "defaultType": default_fmt,
            "defaultPath": default_path,
            "formats": formats
        })

    return entries

def build_catalog():
    root_dir = os.path.abspath(os.path.dirname(__file__))
    catalog = {
        "repo": "EscoffierZhou/SDUFE_140500_2027",
        "title": "SDUFE 140500 智能科学与技术 备考知识库",
        "target": "2027 考研 140500 | 山东财经大学 计算机与人工智能学院",
        "rootDocs": [],
        "subjects": []
    }

    # 1. 处理根目录指引文档
    for rd in ROOT_DOCS:
        p = os.path.join(root_dir, rd['path'])
        if os.path.exists(p):
            catalog["rootDocs"].append({
                "name": rd["name"],
                "path": rd["path"],
                "icon": rd.get("icon", "fa-file-lines"),
                "type": "md"
            })

    # 2. 依次扫描科目目录
    for subj_name, config in SUBJECT_CONFIG.items():
        subj_path = os.path.join(root_dir, subj_name)
        if os.path.exists(subj_path) and os.path.isdir(subj_path):
            children = scan_directory(subj_path, subj_name)
            
            # 统计各种格式文件数
            total_docs = 0
            fmt_counts = {'html': 0, 'pdf': 0, 'md': 0}
            def count_stats(items):
                nonlocal total_docs
                for it in items:
                    if it.get('type') == 'doc':
                        total_docs += 1
                        for f in it.get('formats', {}):
                            fmt_counts[f] = fmt_counts.get(f, 0) + 1
                    elif it.get('type') == 'folder':
                        count_stats(it.get('children', []))
            count_stats(children)

            catalog["subjects"].append({
                "name": subj_name,
                "icon": config["icon"],
                "badge": config["badge"],
                "color": config["color"],
                "stats": {
                    "totalDocs": total_docs,
                    "formats": fmt_counts
                },
                "children": children
            })

    return catalog

def main():
    # 保证 Windows 终端输出不乱码崩溃
    try:
        import sys
        if hasattr(sys.stdout, 'reconfigure'):
            sys.stdout.reconfigure(encoding='utf-8', errors='replace')
    except Exception:
        pass

    print("[*] 正在扫描全仓库 22408 知识库文件...")
    catalog = build_catalog()
    
    js_content = f"// 自动生成的知识库目录数据文件 - 由 generate_catalog.py 自动产生\n// 兼容本地 file:// 协议与 GitHub Pages 在线浏览\nwindow.CATALOG_DATA = {json.dumps(catalog, ensure_ascii=False, indent=2)};\n"
    
    target_file = os.path.join(os.path.dirname(__file__), "catalog.js")
    with open(target_file, "w", encoding="utf-8") as f:
        f.write(js_content)

    print(f"[OK] 成功生成目录索引文件: {target_file}")
    print(f"[OK] 共收录 {len(catalog['subjects'])} 个学科大类与 {len(catalog['rootDocs'])} 个总纲文档。")
    for s in catalog['subjects']:
        stats = s['stats']
        print(f"    - {s['name']}: {stats['totalDocs']} 篇材料 (HTML:{stats['formats'].get('html',0)}, PDF:{stats['formats'].get('pdf',0)}, MD:{stats['formats'].get('md',0)})")

if __name__ == "__main__":
    main()
