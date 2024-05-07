# **说明** 

管理扩展板(具体归类详见[http://mediawiki.hyhsystem.cn](http://mediawiki.hyhsystem.cn))。

# 组件

## ExtBoardD

扩展板守护进程,需要使用root权限运行，通常只能运行一个守护进程实例。

## lsExtBoard

列出扩展板。通常用于显示出扩展板守护进程相关信息。

# DBus接口

扩展板守护进程通过DBus接口对外提供服务。

| 服务名称                 | 说明                 |
| ------------------------ | -------------------- |
| `ExtBoard.Deamon.Server` | 扩展板守护进程服务器 |

## ExtBoard.Deamon.Server

| 对象路径         | 说明             |
| ---------------- | ---------------- |
| `/Deamon/Server` | 守护进程相关信息 |

### /Deamon/Server

| 接口名称          |              |
| ----------------- | ------------ |
| `ExtBoard.Deamon` | 守护进程接口 |

#### ExtBoard.Deamon

| 方法名称 | 说明                           |
| -------- | ------------------------------ |
| Version  | 无参数，返回守护进程版本字符串 |

