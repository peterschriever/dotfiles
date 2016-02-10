"use babel";
/** @jsx etch.dom */

import etch from 'etch';
import {Emitter} from 'atom';

// The header view for the results view, allowing you to add/change connections or change the DB
export default class DataAtomView {
  constructor(useEditorQuery) {
    this.state = {
      isExecuting: false,
      selectedDb: '',
      selectedConnection: '',
      connections: [],
      databases: [],
      useEditorQuery: useEditorQuery
    };

    this.emitter = new Emitter();
    etch.createElement(this);

    this.refs.executeBtn.addEventListener('click', () => { this.executeQuery(); });
    this.refs.cancelBtn.addEventListener('click', () => { this.emitter.emit('data-atom-query-cancel'); });
    this.refs.queryToggle.addEventListener('click', () => { this.queryToggle(); });
    this.refs.connectionBtn.addEventListener('click', () => { this.newConnection(); });
    this.refs.disconnectBtn.addEventListener('click', () => { this.disconnect(); });
    this.refs.connectionList.addEventListener('change', (e) => { this.connectionSelected(e); });
    this.refs.databaseList.addEventListener('change', (e) => { this.databaseSelected(e); });
    this.refs.closeBtn.addEventListener('click', () => { this.close(); });
  }

  render() {
    var queryToggleClass = 'btn btn-default btn-query-toggle ';
    queryToggleClass += this.state.useEditorQuery ? 'btn-query-toggle-up' : 'btn-query-toggle-down selected';
    
    return (<header className='header toolbar'>
      <button className='btn btn-default btn-query-execute' title='Execute' disabled={!this.state.selectedDb || this.state.isExecuting} ref='executeBtn'>Execute</button>
      <button className='btn btn-default btn-query-cancel' title='Cancel execution' disabled={!this.state.isExecuting} ref='cancelBtn'></button>
      <button className={queryToggleClass} title='Toggle between executing content from the active editor or the query panel below' ref='queryToggle'></button>
      <span className='heading-connection-title'>Connection:</span>
      <button className='btn btn-default btn-connect' title='New connection...' ref='connectionBtn'></button>
      <button className='btn btn-default btn-disconnect' title='Disconnect selected connection' ref='disconnectBtn' disabled={this.state.connections.length == 0}></button>
      <select ref='connectionList'>
        <option value='0' disabled='true'>Select connection...</option>
        {this.state.connections.map(con =>
          <option value={con} selected={con == this.state.selectedConnection}>{con}</option>
        )}
      </select>
      <span className='db-label'>Database:</span>
      <select className='db-select' ref='databaseList'>
        <option value='data-atom:select-db' disabled='true'>Select database...</option>
        {this.state.databases.map(db =>
          <option value={db} selected={db == this.state.selectedDb}>{db}</option>
        )}
      </select>
      <span className='heading-close icon-remove-close pull-right' ref='closeBtn'></span>
    </header>);
  }

  getHeight() {
    return this.element.offsetHeight;
  }

  close() {
    atom.commands.dispatch(atom.views.getView(atom.workspace), 'data-atom:toggle-results-view');
  }

  databaseSelected(e) {
    this.state.selectedDb = e.target.options[e.target.selectedIndex].value;
    etch.updateElement(this);
    this.emitter.emit('data-atom-database-changed');
  }

  connectionSelected(e) {
    this.state.selectedConnection = e.target.options[e.target.selectedIndex].value;
    etch.updateElement(this);
    this.emitter.emit('data-atom-connection-changed');
  }

  addConnection(connectionName) {
    this.state.connections.push(connectionName);
    etch.updateElement(this);
  }

  addDbNames(names) {
    this.state.databases = names;
    etch.updateElement(this);
  }

  setSelectedDbName(name) {
    if (name == null)
      name = 'data-atom:select-db';
    this.state.selectedDb = name;
    etch.updateElement(this);
  }

  clearDatabaseSelection() {
    this.state.databases = [];
    etch.updateElement(this);
  }

  setConnection(connectionName) {
    this.state.selectedConnection = connectionName;
    etch.updateElement(this);
  }

  getSelectedConnection() {
    return this.state.selectedConnection;
  }

  getSelectedDatabase() {
    return this.state.selectedDb;
  }

  newConnection() {
    atom.commands.dispatch(atom.views.getView(atom.workspace), 'data-atom:new-connection');
  }

  disconnect() {
    var i = this.state.connections.indexOf(this.state.selectedConnection);
    if (i != -1)
      this.state.connections.splice(i, 1);

    this.state.selectedConnection = '';
    this.state.selectedDb = '';
    this.state.databases = [];
    etch.updateElement(this);
    this.emitter.emit('data-atom-disconnect');
    this.emitter.emit('data-atom-connection-changed');
  }

  onDisconnect(onFunc) {
    return this.emitter.on('data-atom-disconnect', onFunc);
  }

  executeQuery() {
    atom.commands.dispatch(atom.views.getView(atom.workspace), 'data-atom:execute');
  }

  queryToggle() {
    atom.commands.dispatch(atom.views.getView(atom.workspace), 'data-atom:toggle-query-source');
  }

  toggleQuerySource(useEditorQuery) {
    this.state.useEditorQuery = useEditorQuery;
    etch.updateElement(this);
  }

  onConnectionChanged(onConnectionChangedFunc) {
    return this.emitter.on('data-atom-connection-changed', onConnectionChangedFunc);
  }

  onDatabaseChanged(onDatabaseChangedFunc) {
    return this.emitter.on('data-atom-database-changed', onDatabaseChangedFunc);
  }

  onQueryCancel(onQueryCancelFunc) {
    return this.emitter.on('data-atom-query-cancel', onQueryCancelFunc);
  }

  // Let us know that execution has begun. Chance for us to disbale any cnotrols etc.
  executionBegin() {
    this.state.isExecuting = true;
    etch.updateElement(this);
  }
  // Let us know that execution has ended. Chance to re-enable controls etc.
  executionEnd() {
    this.state.isExecuting = false;
    etch.updateElement(this);
  }
}
